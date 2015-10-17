// std
#include <thread>
#include <string>

// Magnum
#include <Magnum/DefaultFramebuffer.h>
#include <Magnum/Platform/Sdl2Application.h>

// GameEngine
#include "GraphicsComponent.hh"
#include "GameLoop.hh"
#include "ModelLoader.hh"
#include "GameObjectFactory.hh"

// Temp
#include "ColoredObject.hh"
#include "TexturedObject.hh"


#include "Application.hh"


GameEngine::Application::Application(const Arguments& arguments)
    : Platform::Application{arguments, Configuration{}.setTitle("Magnum Viewer Example")},
    logicShutdownFlag(true)
{
    Utility::Arguments args;
    args.addArgument("file").setHelp("file", "file to load")
        .setHelp("Loads and displays 3D scene file (such as OpenGEX or COLLADA one) provided on command-line.")
        .parse(arguments.argc, arguments.argv);
    std::string sceneFile(args.value("file"));
    GameEngine::ModelLoader loader(_resourceManager, _drawables, _scene);
    /* loader.loadModel(sceneFile); */

    /* Every scene needs a camera */
    (_cameraObject = new Object3D{&_scene})
        ->translate(Magnum::Vector3::zAxis(5.0f));
    (_camera = new SceneGraph::Camera3D{*_cameraObject})
        ->setAspectRatioPolicy(SceneGraph::AspectRatioPolicy::Extend)
        .setProjectionMatrix(Matrix4::perspectiveProjection(Deg(35.0f), 1.0f, 0.001f, 100))
        .setViewport(defaultFramebuffer.viewport().size());
    Renderer::enable(Renderer::Feature::DepthTest);
    Renderer::enable(Renderer::Feature::FaceCulling);

    gameLogic_ = std::unique_ptr<GameEngine::Logic>(new GameEngine::Logic(loader));
    initLogic();
}

GameEngine::Application::~Application() {
    logicThread_->join();
}

void GameEngine::Application::initLogic() {
    gameLogic_->setup();
    gameLogic_->runInitScript("init_script");
    logicThread_ = std::unique_ptr<std::thread>(new
            std::thread(GameEngine::gameLoop, std::ref(logicShutdownFlag),
                std::ref(*gameLogic_)));
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

void GameEngine::Application::keyReleaseEvent(KeyEvent& event) {
    if(event.key() == Magnum::Platform::Sdl2Application::KeyEvent::Key::Esc) {
        logicShutdownFlag = false;
        exit();
    }
}
