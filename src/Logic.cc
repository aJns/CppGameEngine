#include "Logic.hh"

#include <thread>
#include <OgreVector3.h>

#include "GameObject.hh"
#include "GameLoop.hh"


// TODO: Remove when done
#include <iostream>

GameEngine::Logic::Logic(Ogre::SceneManager* sceneMgr) 
    : sceneMgr_(sceneMgr),
    /* gameObject_(nullptr), */
    gameObject_(),
    shutDown_(nullptr)
{}

GameEngine::Logic::~Logic() {
    std::cout << "**** **** **** **** **** **** **** ****" << std::endl;

    std::cout << "Deleting Logic" << std::endl;

    std::cout << "**** **** **** **** **** **** **** ****" << std::endl;
}

void GameEngine::Logic::runGameLoop() {
    if(shutDown_ == nullptr) {
        return;
    }

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
}

void GameEngine::Logic::processInput() {
}


