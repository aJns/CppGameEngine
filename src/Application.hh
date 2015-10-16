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


// Mostly copied from Magnum example viewer. Code could and probably should be
// divided into separate classes, for example Graphics, InputHandler and maybe
// ResourceManager.
// TODO: Divide into smaller modules, see above comment
using namespace Magnum;

namespace GameEngine {
    typedef Magnum::ResourceManager<Magnum::Buffer, Magnum::Mesh,
            Magnum::Texture2D, Magnum::Shaders::Phong,
            Magnum::Trade::PhongMaterialData> ViewerResourceManager;
    typedef
        Magnum::SceneGraph::Object<Magnum::SceneGraph::DualQuaternionTransformation>
        Object3D;
    typedef
        Magnum::SceneGraph::Scene<Magnum::SceneGraph::DualQuaternionTransformation>
        Scene3D;

    class Application : public Platform::Application {
    public:
        explicit Application(const Arguments& arguments);
        ~Application();

        void initLogic();
    private:
        GameEngine::Logic gameLogic_;
        std::thread* logicThread_;
        bool logicShutdownFlag;

        void viewportEvent(const Vector2i& size) override;
        void drawEvent() override;
        void keyReleaseEvent(Magnum::Platform::Sdl2Application::KeyEvent& event) override;

        ViewerResourceManager _resourceManager;
        Scene3D _scene;
        Object3D *_o, *_cameraObject;
        SceneGraph::Camera3D* _camera;
        SceneGraph::DrawableGroup3D _drawables;
        Magnum::Vector3 _previousPosition;
    };
}

MAGNUM_APPLICATION_MAIN(GameEngine::Application)


#endif // APPLICATION_HH
