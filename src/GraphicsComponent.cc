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
    node_->setPosition(*owner_->position());
    GameEngine::visibleMsg(Ogre::StringConverter::toString(*owner_->position()));
    std::cout << owner_;
}
