// Magnum
#include <Magnum/Trade/PhongMaterialData.h>
#include <Magnum/SceneGraph/Camera.h>

#include "ColoredObject.hh"


typedef ResourceManager<Buffer, Mesh, Texture2D, Shaders::Phong, Trade::PhongMaterialData> ViewerResourceManager;

ColoredObject::ColoredObject(ResourceKey meshId, ResourceKey materialId, Object3D* parent, SceneGraph::DrawableGroup3D* group):
    Object3D{parent}, SceneGraph::Drawable3D{*this, group},
    _mesh{ViewerResourceManager::instance().get<Mesh>(meshId)}, _shader{ViewerResourceManager::instance().get<Shaders::Phong>("color")}
{
    auto material = ViewerResourceManager::instance().get<Trade::PhongMaterialData>(materialId);
    _ambientColor = material->ambientColor();
    _diffuseColor = material->diffuseColor();
    _specularColor = material->specularColor();
    _shininess = material->shininess();
}

void ColoredObject::draw(const Matrix4& transformationMatrix, SceneGraph::Camera3D& camera) {
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
