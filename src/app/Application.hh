#ifndef APPLICATION_HH
#define APPLICATION_HH

// std
#include <memory>
#include <thread>

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
#include "ModelLoader.hh"


using namespace Magnum;

namespace GameEngine {
    typedef ResourceManager<Buffer, Mesh, Texture2D, Shaders::Phong,
            Trade::PhongMaterialData> ViewerResourceManager;
    typedef SceneGraph::Object<SceneGraph::MatrixTransformation3D> Object3D;
    typedef SceneGraph::Scene<SceneGraph::MatrixTransformation3D> Scene3D;

    class Application : public Platform::Application {
    public:
        explicit Application(const Arguments& arguments);
        ~Application();

        void initLogic();
    private:
        std::unique_ptr<GameEngine::Logic> gameLogic_;
        std::unique_ptr<ModelLoader> modelLoader_;

        void viewportEvent(const Vector2i& size) override;
        void drawEvent() override;
        void keyReleaseEvent(Magnum::Platform::Sdl2Application::KeyEvent& event) override;
        void tickEvent() override;

        ViewerResourceManager _resourceManager;
        Scene3D _scene;
        SceneGraph::DrawableGroup3D _drawables;
        Magnum::Vector3 _previousPosition;
        // The scenegraph takes care of these objects
        Object3D* _cameraObject;
        SceneGraph::Camera3D* _camera;
    };
}

MAGNUM_APPLICATION_MAIN(GameEngine::Application)


#endif // APPLICATION_HH
