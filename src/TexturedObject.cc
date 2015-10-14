// Magnum
#include <Magnum/Trade/PhongMaterialData.h>
#include <Magnum/SceneGraph/Camera.h>

#include "TexturedObject.hh"


typedef ResourceManager<Buffer, Mesh, Texture2D, Shaders::Phong,
        Trade::PhongMaterialData> ViewerResourceManager;

TexturedObject::TexturedObject(ResourceKey meshId, ResourceKey materialId,
        ResourceKey diffuseTextureId, Object3D* parent,
        SceneGraph::DrawableGroup3D* group):
    Object3D{parent}, SceneGraph::Drawable3D{*this, group},
    _mesh{ViewerResourceManager::instance().get<Mesh>(meshId)},
    _diffuseTexture{ViewerResourceManager::instance().get<Texture2D>(diffuseTextureId)},
    _shader{ViewerResourceManager::instance().get<Shaders::Phong>("texture")}
{
    auto material = ViewerResourceManager::instance().get<Trade::PhongMaterialData>(materialId);
    _ambientColor = material->ambientColor();
    _specularColor = material->specularColor();
    _shininess = material->shininess();
}

void TexturedObject::draw(const Matrix4& transformationMatrix, SceneGraph::Camera3D& camera) {
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
