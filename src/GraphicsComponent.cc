// GameEngine
#include "Utils.hh"


#include "GraphicsComponent.hh"


GameEngine::GraphicsComponent::GraphicsComponent(GameEngine::GameObject* owner)
    : Component(owner)
{
    /* Ogre::Entity* ogreEntity = sceneMgr.createEntity("ogrehead.mesh"); */
    /* node_ = sceneMgr.getRootSceneNode()->createChildSceneNode(); */
    /* node_->attachObject(ogreEntity); */
}

GameEngine::GraphicsComponent::~GraphicsComponent() {
    /* delete node_; */
}

void GameEngine::GraphicsComponent::update() {
    double x = owner_->position()->x;
    double y = owner_->position()->y;
    double z = owner_->position()->z;
    /* node_->setPosition(x, y, z); */

    double w = owner_->orientation()->w;
    x = owner_->orientation()->x;
    y = owner_->orientation()->y;
    z = owner_->orientation()->z;
    /* Ogre::Quaternion quat(w, x, y, z); */
    /* node_->setOrientation(quat); */
}
