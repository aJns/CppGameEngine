#include "GraphicsComponent.hh"

#include <iostream>

GameEngine::GraphicsComponent::GraphicsComponent(GameEngine::GameObject& owner,
        Ogre::SceneManager& sceneMgr)
    : Component(owner)
{
    Ogre::Entity* ogreEntity = sceneMgr.createEntity("ogrehead.mesh");
    /* Ogre::SceneNode* ogreNode */ 
    node_ = sceneMgr.getRootSceneNode()->createChildSceneNode("TestNode");
    node_->attachObject(ogreEntity);
    /* ogreNode->attachObject(ogreEntity); */
    /* node_ = std::shared_ptr<Ogre::SceneNode>(ogreNode); */

    /* std::cout << node_->getName(); */

    /* node_ = std::shared_ptr<Ogre::SceneNode> */
    /*     (sceneMgr.getRootSceneNode()->createChildSceneNode("ogreNode")); */
    /* node_->attachObject(ogreEntity); */
}

GameEngine::GraphicsComponent::~GraphicsComponent() {
}

void GameEngine::GraphicsComponent::update() {
    node_->setPosition(*owner_->position());
}
