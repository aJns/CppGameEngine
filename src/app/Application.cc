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
    logicShutdownFlag(false)
{
    modelLoader_ = std::unique_ptr<GameEngine::ModelLoader>(new
            GameEngine::ModelLoader(_resourceManager, _drawables, _scene));

    /* Every scene needs a camera */
    (_cameraObject = new Object3D{&_scene})
        ->translate(Magnum::Vector3::zAxis(5.0f));
    (_camera = new SceneGraph::Camera3D{*_cameraObject})
        ->setAspectRatioPolicy(SceneGraph::AspectRatioPolicy::Extend)
        .setProjectionMatrix(Matrix4::perspectiveProjection(Deg(35.0f), 1.0f, 0.001f, 100))
        .setViewport(defaultFramebuffer.viewport().size());
    Renderer::enable(Renderer::Feature::DepthTest);
    Renderer::enable(Renderer::Feature::FaceCulling);

    gameLogic_ = std::unique_ptr<GameEngine::Logic>(new
            GameEngine::Logic(modelLoader_.get()));
    initLogic();
}

GameEngine::Application::~Application() {
}

void GameEngine::Application::initLogic() {
    gameLogic_->setup();
    gameLogic_->runInitScript("init_script");
    setMinimalLoopPeriod(33);
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

void GameEngine::Application::tickEvent() {
    gameLogic_->update();
}