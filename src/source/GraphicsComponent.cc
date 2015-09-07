// Ogre3D
#include <OgreString.h>

// GameEngine
#include "Utils.hh"

#include "GraphicsComponent.hh"


GameEngine::GraphicsComponent::GraphicsComponent(GameEngine::GameObject* owner,
        Ogre::SceneManager& sceneMgr)
    : Component(owner)
{
    Ogre::Entity* ogreEntity = sceneMgr.createEntity("ogrehead.mesh");
    node_ = sceneMgr.getRootSceneNode()->createChildSceneNode("TestNode");
    node_->attachObject(ogreEntity);
}

GameEngine::GraphicsComponent::~GraphicsComponent() {
    delete node_;
}

void GameEngine::GraphicsComponent::update() {
    double x = owner_->position()->x;
    double y = owner_->position()->y;
    double z = owner_->position()->z;
    node_->setPosition(x, y, z);
}
