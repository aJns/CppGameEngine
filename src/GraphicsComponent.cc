#include "GraphicsComponent.hh"

#include <iostream>

GameEngine::GraphicsComponent::GraphicsComponent(GameEngine::GameObject& owner,
        Ogre::SceneManager& sceneMgr)
    : Component(owner)
{
    Ogre::Entity* ogreEntity = sceneMgr.createEntity("ogrehead.mesh");
    node_ = std::shared_ptr<Ogre::SceneNode>
        (sceneMgr.getRootSceneNode()->createChildSceneNode("ogreNode"));
    node_->attachObject(ogreEntity);
    std::cout << node_->getName() << "\n";
}

GameEngine::GraphicsComponent::~GraphicsComponent() {
}

std::shared_ptr<Ogre::SceneNode> GameEngine::GraphicsComponent::getNode() {
    return node_;
}

void GameEngine::GraphicsComponent::update() {
}
