// std
#include <thread>

// Magnum
#include <Magnum/DefaultFramebuffer.h>

// GameEngine
#include "GraphicsComponent.hh"
#include "GameLoop.hh"


#include "Application.hh"


using Magnum::operator "" _degf;

GameEngine::Application::Application(const Arguments& arguments)
    : Magnum::Platform::Application{arguments},
    gameLogic_(nullptr)
{
    /* using namespace Magnum; */
    /* Configure camera */
    cameraObject_ = new Magnum::SceneGraph::Object<Magnum::SceneGraph::MatrixTransformation3D>{&scene_};
    cameraObject_->translate(Magnum::Vector3::zAxis(5.0f));
    camera_ = new Magnum::SceneGraph::Camera3D{*cameraObject_};
    camera_->setAspectRatioPolicy(Magnum::SceneGraph::AspectRatioPolicy::Extend)
        .setProjectionMatrix(Magnum::Matrix4::perspectiveProjection(35.0_degf, 4.0f/3.0f, 0.001f, 100.0f))
        .setViewport(Magnum::defaultFramebuffer.viewport().size());

    /* TODO: Prepare your objects here and add them to the scene */
}

GameEngine::Application::~Application() {
    if (gameLogic_) delete gameLogic_;
}

void GameEngine::Application::init() {
    bool shutdown = false;
    gameLogic_ = new GameEngine::Logic();
    gameLogic_->setup(shutdown);
    gameLogic_->runInitScript("init_script");
    std::thread logicThread(GameEngine::gameLoop, std::ref(shutdown),
            std::ref(*gameLogic_));

    logicThread.join();
}

void GameEngine::Application::drawEvent() {
    Magnum::defaultFramebuffer.clear(Magnum::FramebufferClear::Color);

    camera_->draw(drawables_);

    swapBuffers();
}
