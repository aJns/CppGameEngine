#include "GameObject.hh"

// Need to include things here to work around circular dependencies
#include "GraphicsComponent.hh"

GameEngine::GameObject::GameObject()
    : position_(0,0,0),
    graphComp_(nullptr)
{}

GameEngine::GameObject::~GameObject() {
}

void GameEngine::GameObject::addGraphicsComponent(Ogre::SceneManager& sceneMgr) {
    /* Ogre::Entity* ogreEntity = sceneMgr.createEntity("ogrehead.mesh"); */
    /* Ogre::SceneNode* ogreNode = sceneMgr.getRootSceneNode()->createChildSceneNode("TestNode"); */
    /* ogreNode->attachObject(ogreEntity); */

    graphComp_ = std::make_shared<GameEngine::GraphicsComponent>
        (GameEngine::GraphicsComponent(*this, sceneMgr));
}

void GameEngine::GameObject::update() {
    if (graphComp_ != nullptr) {
        graphComp_->update();
    }
}

std::shared_ptr<Ogre::Vector3> const GameEngine::GameObject::position() const {
    return std::make_shared<Ogre::Vector3>(position_);
}

void GameEngine::GameObject::translate(std::shared_ptr<Ogre::Vector3> const vector) {
    position_ += *vector;
}

void GameEngine::GameObject::moveTo(std::shared_ptr<Ogre::Vector3> const vector) {
    position_ = *vector;
}
