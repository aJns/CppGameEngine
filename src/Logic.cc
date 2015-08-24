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
}

void GameEngine::Logic::setup(const bool& shutDown) {
    shutDown_ = &shutDown;
    /* gameObject_ = std::make_shared<GameEngine::GameObject>(); */
    /* gameObject_->addGraphicsComponent(*sceneMgr_); */
    gameObject_.addGraphicsComponent(*sceneMgr_);
}

void GameEngine::Logic::updateLogic() {
    Ogre::Vector3 vector(1, 1, 1);
    gameObject_.translate(vector);
    gameObject_.update();
}

void GameEngine::Logic::processInput() {
}


