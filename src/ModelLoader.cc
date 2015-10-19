// Magnum
#include <Magnum/Math/Angle.h>

// Temp
#include "ColoredObject.hh"
#include "TexturedObject.hh"


#include "ModelLoader.hh"


GameEngine::ModelLoader::ModelLoader(ViewerResourceManager* resourceManager,
        Magnum::SceneGraph::DrawableGroup3D* drawables,
        Scene3D* scene)
    : resourceManager_(resourceManager),
    drawables_(drawables),
    _scene(scene)
{
}

void GameEngine::ModelLoader::loadModel(Object3D* object, std::string sceneFile) {
    /* Phong shader instances */
    resourceManager_->set("color", new Shaders::Phong)
        .set("texture", new Shaders::Phong{Shaders::Phong::Flag::DiffuseTexture});

    /* Fallback material, texture and mesh in case the data are not present or
       cannot be loaded */
    auto material = new Trade::PhongMaterialData{{}, 50.0f};
    material->ambientColor() = {0.0f, 0.0f, 0.0f};
    material->diffuseColor() = {0.9f, 0.9f, 0.9f};
    material->specularColor() = {1.0f, 1.0f, 1.0f};
    resourceManager_->setFallback(material)
        .setFallback(new Texture2D)
        .setFallback(new Mesh);

    /* Load scene importer plugin */
    PluginManager::Manager<Trade::AbstractImporter> manager{MAGNUM_PLUGINS_IMPORTER_DIR};
    std::unique_ptr<Trade::AbstractImporter> importer = manager.loadAndInstantiate("AnySceneImporter");
    if(!importer)
        std::exit(1);
    Debug() << "Opening file" << sceneFile;

    /* Load file */
    if(!importer->openFile(sceneFile))
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
        resourceManager_->set(ResourceKey{i}, static_cast<Trade::PhongMaterialData*>(materialData.release()));
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
        resourceManager_->set(ResourceKey{i}, texture, ResourceDataState::Final, ResourcePolicy::Manual);
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
        resourceManager_->set(ResourceKey{i}, new Mesh{std::move(mesh)}, ResourceDataState::Final, ResourcePolicy::Manual);
        resourceManager_->set(std::to_string(i) + "-vertices", buffer.release(), ResourceDataState::Final, ResourcePolicy::Manual);
        if(indexBuffer)
            resourceManager_->set(std::to_string(i) + "-indices", indexBuffer.release(), ResourceDataState::Final, ResourcePolicy::Manual);
    }
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
            addObject(*importer, object, objectId);

        /* The format has no scene support, display just the first loaded mesh with
           default material and be done with it */
    } else if(resourceManager_->state<Mesh>(ResourceKey{0}) == ResourceState::Final)
        new ColoredObject(ResourceKey{0}, ResourceKey(-1), object, drawables_);

    /* Materials were consumed by objects and they are not needed anymore. Also
       free all texture/mesh data that weren't referenced by any object. */
    resourceManager_->setFallback<Trade::PhongMaterialData>(nullptr)
        .clear<Trade::PhongMaterialData>()
        .free<Texture2D>()
        .free<Mesh>();
}

void GameEngine::ModelLoader::addObject(Magnum::Trade::AbstractImporter& importer,
        Object3D* parent, Magnum::UnsignedInt i) {
    Magnum::Debug() << "Importing object" << i << importer.object3DName(i);
    Object3D* object = nullptr;
    std::unique_ptr<Magnum::Trade::ObjectData3D> objectData = importer.object3D(i);
    if(!objectData) {
        Magnum::Error() << "Cannot import object, skipping";
        return;
    }

    /* Only meshes for now */
    if(objectData->instanceType() == Magnum::Trade::ObjectInstanceType3D::Mesh) {
        Magnum::Int materialId = static_cast<Magnum::Trade::MeshObjectData3D*>(objectData.get())->material();

        /* Decide what object to add based on material type */
        auto materialData = resourceManager_->get<Trade::PhongMaterialData>(ResourceKey(materialId));

        /* Color-only material */
        if(!materialData->flags()) {
            object = new ColoredObject(ResourceKey(objectData->instance()),
                    ResourceKey(materialId),
                    parent, drawables_);
            object->setTransformation(objectData->transformation());

            /* Diffuse texture material */
        } else if(materialData->flags() == Trade::PhongMaterialData::Flag::DiffuseTexture) {
            object = new TexturedObject(ResourceKey(objectData->instance()),
                    ResourceKey(materialId),
                    ResourceKey(materialData->diffuseTexture()),
                    parent, drawables_);
            object->setTransformation(objectData->transformation());

            /* No other material types are supported yet */
        } else {
            Warning() << "Texture combination of material"
                << materialId << importer.materialName(materialId)
                << "is not supported, using default material instead";
            object = new ColoredObject(ResourceKey(objectData->instance()),
                    ResourceKey(-1),
                    parent, drawables_);
            object->setTransformation(objectData->transformation());
        }
    }
    /* Create parent object for children, if it doesn't already exist */
    if(!object && !objectData->children().empty()) object = new Object3D(parent);

    /* Recursively add children */
    for(std::size_t id: objectData->children())
        addObject(importer, object, id);
}

GameEngine::Scene3D* GameEngine::ModelLoader::getScene() {
    return _scene;
}
