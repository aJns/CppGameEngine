#ifndef COLOREDOBJECT_HH
#define COLOREDOBJECT_HH


#include <Magnum/SceneGraph/DualQuaternionTransformation.h>
#include <Magnum/SceneGraph/Drawable.h>
#include <Magnum/Shaders/Phong.h>
#include <Magnum/Resource.h>
#include <Magnum/Mesh.h>
#include <Magnum/Texture.h>

using namespace Magnum;

typedef SceneGraph::Object<SceneGraph::DualQuaternionTransformation> Object3D;

class ColoredObject: public Object3D, SceneGraph::Drawable3D {
public:
    explicit ColoredObject(ResourceKey meshId, ResourceKey materialId, Object3D* parent, SceneGraph::DrawableGroup3D* group);
private:
    void draw(const Matrix4& transformationMatrix, SceneGraph::Camera3D& camera) override;
    Resource<Mesh> _mesh;
    Resource<Shaders::Phong> _shader;
    Magnum::Vector3 _ambientColor,
        _diffuseColor,
        _specularColor;
    Float _shininess;
};


#endif // COLOREDOBJECT_HH
