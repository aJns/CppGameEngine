// std
#include <thread>

// Ogre3D
#include <OgreVector3.h>

// GameEngine
#include "GameObject.hh"
#include "GameLoop.hh"
#include "Utils.hh"

#include "Logic.hh"


GameEngine::Logic::Logic(Ogre::SceneManager* sceneMgr) 
    : sceneMgr_(sceneMgr),
    /* gameObject_(nullptr), */
    gameObject_(),
    shutDown_(nullptr)
{}

GameEngine::Logic::~Logic() {
}

void GameEngine::Logic::runGameLoop() {
    if(shutDown_ == nullptr) {
        return;
    }

    GameEngine::visibleMsg("running loop...");

    /* std::thread logicThread(GameEngine::gameLoop, *shutDown_, std::ref(*this)); */
}

void GameEngine::Logic::setup(const bool& shutDown) {
    shutDown_ = &shutDown;
    /* gameObject_ = std::make_shared<GameEngine::GameObject>(); */
    /* gameObject_->addGraphicsComponent(*sceneMgr_); */
    gameObject_.addGraphicsComponent(*sceneMgr_);
}

void GameEngine::Logic::updateLogic() {
    Ogre::Vector3 vector(10, 10, 10);
    /* gameObject_->translate(std::make_shared<Ogre::Vector3>(vector)); */
    gameObject_.translate(vector);
    gameObject_.update();

    GameEngine::visibleMsg("Moved GameObject");
}

void GameEngine::Logic::processInput() {
}


