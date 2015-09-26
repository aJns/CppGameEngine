// GameEngine
#include "GraphicsComponent.hh"
#include "GameLoop.hh"

// std
#include <thread>


#include "Application.hh"


GameEngine::Application::Application()
    : root_(0),
    camera_(0),
    sceneMgr_(0),
    window_(0),
    resourcesCfg_(Ogre::StringUtil::BLANK),
    pluginsCfg_(Ogre::StringUtil::BLANK),
    trayMgr_(0),
    cameraMan_(0),
    detailsPanel_(0),
    cursorWasVisible_(false),
    shutDown_(false),
    inputManager_(0),
    mouse_(0),
    keyboard_(0),
    gameLogic_(nullptr)
{
}

GameEngine::Application::~Application() {
    if (gameLogic_) delete gameLogic_;
}

void GameEngine::Application::init() {
    bool shutdown = false;
    gameLogic_ = new GameEngine::Logic(sceneMgr_);
    gameLogic_->setup(shutdown);
    gameLogic_->runInitScript("init_script");
    std::thread logicThread(GameEngine::gameLoop, std::ref(shutdown),
            std::ref(*gameLogic_));

    logicThread.join();
}
