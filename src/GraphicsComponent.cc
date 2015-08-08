#include "GraphicsComponent.hh"

GameEngine::GraphicsComponent::GraphicsComponent(GameEngine::GameObject& owner,
        Ogre::SceneManager& sceneMgr)
    : Component(owner),
    node_(nullptr)
{
    Ogre::Entity* ogreEntity = sceneMgr.createEntity("ogrehead.mesh");
    Ogre::SceneNode* ogreNode = sceneMgr.getRootSceneNode()->createChildSceneNode();
    ogreNode->attachObject(ogreEntity);
    std::shared_ptr<Ogre::SceneNode> smartOgre(ogreNode);
    node_ = smartOgre;
}

GameEngine::GraphicsComponent::~GraphicsComponent() {
}

std::shared_ptr<Ogre::SceneNode> GameEngine::GraphicsComponent::getNode() {
    return node_;
}
