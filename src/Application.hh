#ifndef APPLICATION_HH
#define APPLICATION_HH

// std
#include <memory>

// Magnum
#include <Corrade/PluginManager/Manager.h>
#include <Corrade/Utility/Arguments.h>
#include <Magnum/Buffer.h>
#include <Magnum/DefaultFramebuffer.h>
#include <Magnum/TextureFormat.h>
#include <Magnum/Mesh.h>
#include <Magnum/PixelFormat.h>
#include <Magnum/Renderer.h>
#include <Magnum/ResourceManager.h>
#include <Magnum/Texture.h>
#include <Magnum/MeshTools/Compile.h>
#include <Magnum/Platform/Sdl2Application.h>
#include <Magnum/SceneGraph/Camera.h>
#include <Magnum/SceneGraph/Drawable.h>
#include <Magnum/SceneGraph/MatrixTransformation3D.h>
#include <Magnum/SceneGraph/Scene.h>
#include <Magnum/Shaders/Phong.h>
#include <Magnum/Trade/AbstractImporter.h>
#include <Magnum/Trade/ImageData.h>
#include <Magnum/Trade/MeshData3D.h>
#include <Magnum/Trade/MeshObjectData3D.h>
#include <Magnum/Trade/PhongMaterialData.h>
#include <Magnum/Trade/SceneData.h>
#include <Magnum/Trade/TextureData.h>

#include "configure.h"

// GameEngine
#include "Logic.hh"
#include "ApplicationInterface.hh"


// Mostly copied from Magnum example viewer. Code could and probably should be
// divided into separate classes, for example Graphics, InputHandler and maybe
// ResourceManager.
using namespace Magnum;

namespace GameEngine {
    typedef ResourceManager<Buffer, Mesh, Texture2D, Shaders::Phong, Trade::PhongMaterialData> ViewerResourceManager;
    typedef SceneGraph::Object<SceneGraph::MatrixTransformation3D> Object3D;
    typedef SceneGraph::Scene<SceneGraph::MatrixTransformation3D> Scene3D;

    class Application : public Platform::Application, public GameEngine::ApplicationInterface {
    public:
        explicit Application(const Arguments& arguments);
        ~Application();

        void initLogic() override;
    private:
        GameEngine::Logic* gameLogic_;

        void viewportEvent(const Vector2i& size) override;
        void drawEvent() override;
        /* void mousePressEvent(MouseEvent& event) override; */
        /* void mouseReleaseEvent(MouseEvent& event) override; */
        /* void mouseMoveEvent(MouseMoveEvent& event) override; */
        /* Vector3 positionOnSphere(const Vector2i& _position) const; */
        void addObject(Trade::AbstractImporter& importer, Object3D* parent, UnsignedInt i);
        ViewerResourceManager _resourceManager;
        Scene3D _scene;
        Object3D *_o, *_cameraObject;
        SceneGraph::Camera3D* _camera;
        SceneGraph::DrawableGroup3D _drawables;
        Magnum::Vector3 _previousPosition;
    };

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
}

MAGNUM_APPLICATION_MAIN(GameEngine::Application)


#endif // APPLICATION_HH
