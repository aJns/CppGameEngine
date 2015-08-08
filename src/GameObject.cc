#include "GameObject.hh"

// Need to include things here to work around circular dependencies
#include "GraphicsComponent.hh"

GameEngine::GameObject::GameObject()
    : position_(0,0,0),
    graphComp_(nullptr)
{}

GameEngine::GameObject::~GameObject() {
}

std::shared_ptr<Ogre::Vector3> GameEngine::GameObject::position() {
    return std::make_shared<Ogre::Vector3>(position_);
}

void GameEngine::GameObject::addGraphicsComponent(Ogre::SceneManager& sceneMgr) {
    std::shared_ptr<GameEngine::GraphicsComponent> smartGraph(
            new GameEngine::GraphicsComponent(*this, sceneMgr));
    graphComp_ = smartGraph;
}
