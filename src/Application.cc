// std
#include <thread>

// Magnum
#include <Magnum/DefaultFramebuffer.h>

// GameEngine
#include "GraphicsComponent.hh"
#include "GameLoop.hh"


#include "Application.hh"


GameEngine::Application::Application(const Arguments& arguments)
    : Platform::Application{arguments, Configuration{}.setTitle("Magnum Viewer Example")} 
{
    Utility::Arguments args;
    args.addArgument("file").setHelp("file", "file to load")
        .setHelp("Loads and displays 3D scene file (such as OpenGEX or COLLADA one) provided on command-line.")
        .parse(arguments.argc, arguments.argv);
    /* Phong shader instances */
    _resourceManager.set("color", new Shaders::Phong)
        .set("texture", new Shaders::Phong{Shaders::Phong::Flag::DiffuseTexture});
    /* Fallback material, texture and mesh in case the data are not present or
       cannot be loaded */
    auto material = new Trade::PhongMaterialData{{}, 50.0f};
    material->ambientColor() = {0.0f, 0.0f, 0.0f};
    material->diffuseColor() = {0.9f, 0.9f, 0.9f};
    material->specularColor() = {1.0f, 1.0f, 1.0f};
    _resourceManager.setFallback(material)
        .setFallback(new Texture2D)
        .setFallback(new Mesh);
    /* Every scene needs a camera */
    (_cameraObject = new Object3D{&_scene})
        ->translate(Magnum::Vector3::zAxis(5.0f));
    (_camera = new SceneGraph::Camera3D{*_cameraObject})
        ->setAspectRatioPolicy(SceneGraph::AspectRatioPolicy::Extend)
        .setProjectionMatrix(Matrix4::perspectiveProjection(Deg(35.0f), 1.0f, 0.001f, 100))
        .setViewport(defaultFramebuffer.viewport().size());
    Renderer::enable(Renderer::Feature::DepthTest);
    Renderer::enable(Renderer::Feature::FaceCulling);
    /* Load scene importer plugin */
    PluginManager::Manager<Trade::AbstractImporter> manager{MAGNUM_PLUGINS_IMPORTER_DIR};
    std::unique_ptr<Trade::AbstractImporter> importer = manager.loadAndInstantiate("AnySceneImporter");
    if(!importer)
        std::exit(1);
    Debug() << "Opening file" << args.value("file");
    /* Load file */
    if(!importer->openFile(args.value("file")))
        std::exit(4);
    /* Load all materials */
    for(UnsignedInt i = 0; i != importer->materialCount(); ++i) {
        Debug() << "Importing material" << i << importer->materialName(i);
        std::unique_ptr<Trade::AbstractMaterialData> materialData = importer->material(i);
        if(!materialData || materialData->type() != Trade::MaterialType::Phong) {
            Warning() << "Cannot load material, skipping";
            continue;
        }
        /* Save the material */
        _resourceManager.set(ResourceKey{i}, static_cast<Trade::PhongMaterialData*>(materialData.release()));
    }
    /* Load all textures */
    for(UnsignedInt i = 0; i != importer->textureCount(); ++i) {
        Debug() << "Importing texture" << i << importer->textureName(i);
        std::optional<Trade::TextureData> textureData = importer->texture(i);
        if(!textureData || textureData->type() != Trade::TextureData::Type::Texture2D) {
            Warning() << "Cannot load texture, skipping";
            continue;
        }
        Debug() << "Importing image" << textureData->image() << importer->image2DName(textureData->image());
        std::optional<Trade::ImageData2D> imageData = importer->image2D(textureData->image());
        if(!imageData || (imageData->format() != PixelFormat::RGB
#ifndef MAGNUM_TARGET_GLES
                    && imageData->format() != PixelFormat::BGR
#endif
                    ))
        {
            Warning() << "Cannot load texture image, skipping";
            continue;
        }
        /* Configure texture */
        auto texture = new Texture2D;
        texture->setMagnificationFilter(textureData->magnificationFilter())
            .setMinificationFilter(textureData->minificationFilter(), textureData->mipmapFilter())
            .setWrapping(textureData->wrapping().xy())
            .setStorage(1, TextureFormat::RGB8, imageData->size())
            .setSubImage(0, {}, *imageData)
            .generateMipmap();
        /* Save it */
        _resourceManager.set(ResourceKey{i}, texture, ResourceDataState::Final, ResourcePolicy::Manual);
    }
    /* Load all meshes */
    for(UnsignedInt i = 0; i != importer->mesh3DCount(); ++i) {
        Debug() << "Importing mesh" << i << importer->mesh3DName(i);
        std::optional<Trade::MeshData3D> meshData = importer->mesh3D(i);
        if(!meshData || !meshData->hasNormals() || meshData->primitive() != MeshPrimitive::Triangles) {
            Warning() << "Cannot load mesh, skipping";
            continue;
        }
        /* Compile the mesh */
        Mesh mesh{NoCreate};
        std::unique_ptr<Buffer> buffer, indexBuffer;
        std::tie(mesh, buffer, indexBuffer) = MeshTools::compile(*meshData, BufferUsage::StaticDraw);
        /* Save things */
        _resourceManager.set(ResourceKey{i}, new Mesh{std::move(mesh)}, ResourceDataState::Final, ResourcePolicy::Manual);
        _resourceManager.set(std::to_string(i) + "-vertices", buffer.release(), ResourceDataState::Final, ResourcePolicy::Manual);
        if(indexBuffer)
            _resourceManager.set(std::to_string(i) + "-indices", indexBuffer.release(), ResourceDataState::Final, ResourcePolicy::Manual);
    }
    /* Default object, parent of all (for manipulation) */
    _o = new Object3D{&_scene};
    /* Load the scene */
    if(importer->defaultScene() != -1) {
        Debug() << "Adding default scene" << importer->sceneName(importer->defaultScene());
        std::optional<Trade::SceneData> sceneData = importer->scene(importer->defaultScene());
        if(!sceneData) {
            Error() << "Cannot load scene, exiting";
            return;
        }
        /* Recursively add all children */
        for(UnsignedInt objectId: sceneData->children3D())
            addObject(*importer, _o, objectId);
        /* The format has no scene support, display just the first loaded mesh with
           default material and be done with it */
    } else if(_resourceManager.state<Mesh>(ResourceKey{0}) == ResourceState::Final)
        new ColoredObject(ResourceKey{0}, ResourceKey(-1), _o, &_drawables);
    /* Materials were consumed by objects and they are not needed anymore. Also
       free all texture/mesh data that weren't referenced by any object. */
            _resourceManager.setFallback<Trade::PhongMaterialData>(nullptr)
                .clear<Trade::PhongMaterialData>()
                .free<Texture2D>()
                .free<Mesh>();
}

GameEngine::Application::~Application() {
    if (gameLogic_) delete gameLogic_;
}

void GameEngine::Application::initLogic() {
    bool shutdown = false;
    gameLogic_ = new GameEngine::Logic();
    gameLogic_->setup(shutdown);
    gameLogic_->runInitScript("init_script");
    std::thread logicThread(GameEngine::gameLoop, std::ref(shutdown),
            std::ref(*gameLogic_));

    logicThread.join();
}

void GameEngine::Application::addObject(Trade::AbstractImporter& importer, Object3D* parent, UnsignedInt i) {
    Debug() << "Importing object" << i << importer.object3DName(i);
    Object3D* object = nullptr;
    std::unique_ptr<Trade::ObjectData3D> objectData = importer.object3D(i);
    if(!objectData) {
        Error() << "Cannot import object, skipping";
        return;
    }
    /* Only meshes for now */
    if(objectData->instanceType() == Trade::ObjectInstanceType3D::Mesh) {
        Int materialId = static_cast<Trade::MeshObjectData3D*>(objectData.get())->material();
        /* Decide what object to add based on material type */
        auto materialData = _resourceManager.get<Trade::PhongMaterialData>(ResourceKey(materialId));
        /* Color-only material */
        if(!materialData->flags()) {
            object = new ColoredObject(ResourceKey(objectData->instance()),
                    ResourceKey(materialId),
                    parent, &_drawables);
            object->setTransformation(objectData->transformation());
            /* Diffuse texture material */
        } else if(materialData->flags() == Trade::PhongMaterialData::Flag::DiffuseTexture) {
            object = new TexturedObject(ResourceKey(objectData->instance()),
                    ResourceKey(materialId),
                    ResourceKey(materialData->diffuseTexture()),
                    parent, &_drawables);
            object->setTransformation(objectData->transformation());
            /* No other material types are supported yet */
        } else {
            Warning() << "Texture combination of material"
                << materialId << importer.materialName(materialId)
                << "is not supported, using default material instead";
            object = new ColoredObject(ResourceKey(objectData->instance()),
                    ResourceKey(-1),
                    parent, &_drawables);
            object->setTransformation(objectData->transformation());
        }
    }
    /* Create parent object for children, if it doesn't already exist */
    if(!object && !objectData->children().empty()) object = new Object3D(parent);
    /* Recursively add children */
    for(std::size_t id: objectData->children())
        addObject(importer, object, id);
}

void GameEngine::Application::viewportEvent(const Vector2i& size) {
    defaultFramebuffer.setViewport({{}, size});
    _camera->setViewport(size);
}

void GameEngine::Application::drawEvent() {
    defaultFramebuffer.clear(FramebufferClear::Color|FramebufferClear::Depth);
    _camera->draw(_drawables);
    swapBuffers();
}

/* void GameEngine::Application::mousePressEvent(MouseEvent& event) { */
/*     switch(event.button()) { */
/*         case MouseEvent::Button::Left: */
/*             _previousPosition = positionOnSphere(event.position()); */
/*             break; */
/*         case MouseEvent::Button::WheelUp: */
/*         case MouseEvent::Button::WheelDown: { */
/*                                                 /1* Distance to origin *1/ */
/*                                                 Float distance = _cameraObject->transformation().translation().z(); */
/*                                                 /1* Move 15% of the distance back or forward *1/ */
/*                                                 distance *= 1 - (event.button() == MouseEvent::Button::WheelUp ? 1/0.85f : 0.85f); */
/*                                                 _cameraObject->translate(Vector3::zAxis(distance)); */
/*                                                 redraw(); */
/*                                                 break; */
/*                                             } */
/*         default: ; */
/*     } */
/* } */
/* void GameEngine::Application::mouseReleaseEvent(MouseEvent& event) { */
/*     if(event.button() == MouseEvent::Button::Left) */
/*         _previousPosition = Vector3(); */
/* } */
/* Vector3 GameEngine::Application::positionOnSphere(const Vector2i& position) const { */
/*     Vector2 positionNormalized = Vector2(position*2)/Vector2(_camera->viewport()) - Vector2(1.0f); */
/*     Float length = positionNormalized.length(); */
/*     Vector3 result(length > 1.0f ? Vector3(positionNormalized, 0.0f) : Vector3(positionNormalized, 1.0f - length)); */
/*     result.y() *= -1.0f; */
/*     return result.normalized(); */
/* } */
/* void GameEngine::Application::mouseMoveEvent(MouseMoveEvent& event) { */
/*     if(!(event.buttons() & MouseMoveEvent::Button::Left)) return; */
/*     Vector3 currentPosition = positionOnSphere(event.position()); */
/*     Vector3 axis = Math::cross(_previousPosition, currentPosition); */
/*     if(_previousPosition.length() < 0.001f || axis.length() < 0.001f) return; */
/*     _o->rotate(Math::angle(_previousPosition, currentPosition), axis.normalized()); */
/*     _previousPosition = currentPosition; */
/*     redraw(); */
/* } */

GameEngine::ColoredObject::ColoredObject(ResourceKey meshId, ResourceKey materialId, Object3D* parent, SceneGraph::DrawableGroup3D* group):
    Object3D{parent}, SceneGraph::Drawable3D{*this, group},
    _mesh{ViewerResourceManager::instance().get<Mesh>(meshId)}, _shader{ViewerResourceManager::instance().get<Shaders::Phong>("color")}
{
    auto material = ViewerResourceManager::instance().get<Trade::PhongMaterialData>(materialId);
    _ambientColor = material->ambientColor();
    _diffuseColor = material->diffuseColor();
    _specularColor = material->specularColor();
    _shininess = material->shininess();
}
GameEngine::TexturedObject::TexturedObject(ResourceKey meshId, ResourceKey materialId, ResourceKey diffuseTextureId, Object3D* parent, SceneGraph::DrawableGroup3D* group):
    Object3D{parent}, SceneGraph::Drawable3D{*this, group},
    _mesh{ViewerResourceManager::instance().get<Mesh>(meshId)}, _diffuseTexture{ViewerResourceManager::instance().get<Texture2D>(diffuseTextureId)}, _shader{ViewerResourceManager::instance().get<Shaders::Phong>("texture")}
{
    auto material = ViewerResourceManager::instance().get<Trade::PhongMaterialData>(materialId);
    _ambientColor = material->ambientColor();
    _specularColor = material->specularColor();
    _shininess = material->shininess();
}
void GameEngine::ColoredObject::draw(const Matrix4& transformationMatrix, SceneGraph::Camera3D& camera) {
    _shader->setAmbientColor(_ambientColor)
        .setDiffuseColor(_diffuseColor)
        .setSpecularColor(_specularColor)
        .setShininess(_shininess)
        .setLightPosition(camera.cameraMatrix().transformPoint({-3.0f, 10.0f, 10.0f}))
        .setTransformationMatrix(transformationMatrix)
        .setNormalMatrix(transformationMatrix.rotation())
        .setProjectionMatrix(camera.projectionMatrix());
    _mesh->draw(*_shader);
}
void GameEngine::TexturedObject::draw(const Matrix4& transformationMatrix, SceneGraph::Camera3D& camera) {
    _shader->setAmbientColor(_ambientColor)
        .setDiffuseTexture(*_diffuseTexture)
        .setSpecularColor(_specularColor)
        .setShininess(_shininess)
        .setLightPosition(camera.cameraMatrix().transformPoint({-3.0f, 10.0f, 10.0f}))
        .setTransformationMatrix(transformationMatrix)
        .setNormalMatrix(transformationMatrix.rotation())
        .setProjectionMatrix(camera.projectionMatrix());
    _mesh->draw(*_shader);
}
