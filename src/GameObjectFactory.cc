#include "GameObjectFactory.hh"

void GameEngine::GameObjectFactory::createObject() {
    objectVector_->push_back(new GameEngine::GameObject());
}
