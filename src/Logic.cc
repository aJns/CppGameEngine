#include "Logic.hh"

#include <thread>

#include "GameObject.hh"

GameEngine::Logic::Logic(Ogre::SceneManager* sceneMgr) 
    : sceneMgr_(sceneMgr)
{}

GameEngine::Logic::~Logic() {
}

void GameEngine::Logic::runGameLoop() {
}

void GameEngine::Logic::setup() {
    GameEngine::GameObject object;
    object.addGraphicsComponent(*sceneMgr_);
}

void GameEngine::Logic::updateLogic() {
}

void GameEngine::Logic::processInput() {
}


