// Temp
#include "ColoredObject.hh"
#include "TexturedObject.hh"


#include "ModelLoader.hh"


GameEngine::ModelLoader::ModelLoader(ViewerResourceManager& resourceManager,
        Magnum::SceneGraph::DrawableGroup3D& drawables)
    : resourceManager_(&resourceManager),
    drawables_(&drawables)
{
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
