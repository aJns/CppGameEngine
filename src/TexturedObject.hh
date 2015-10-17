#ifndef TEXTUREDOBJECT_HH
#define TEXTUREDOBJECT_HH


#include <Magnum/SceneGraph/MatrixTransformation3D.h>
#include <Magnum/SceneGraph/Drawable.h>
#include <Magnum/Shaders/Phong.h>
#include <Magnum/Resource.h>
#include <Magnum/Mesh.h>
#include <Magnum/Texture.h>

using namespace Magnum;

typedef SceneGraph::Object<SceneGraph::MatrixTransformation3D> Object3D;

class TexturedObject: public Object3D, SceneGraph::Drawable3D {
public:
    explicit TexturedObject(ResourceKey meshId, ResourceKey materialId, ResourceKey diffuseTextureId, Object3D* parent, SceneGraph::DrawableGroup3D* group);
private:
    void draw(const Matrix4& transformationMatrix, SceneGraph::Camera3D& camera) override;
    Resource<Mesh> _mesh;
    Resource<Texture2D> _diffuseTexture;
    Resource<Shaders::Phong> _shader;
    Magnum::Vector3 _ambientColor,
        _specularColor;
    Float _shininess;
};


#endif // TEXTUREDOBJECT_HH
