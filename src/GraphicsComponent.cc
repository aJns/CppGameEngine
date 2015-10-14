// Magnum
#include "Magnum/SceneGraph/SceneGraph.h"
#include "Magnum/SceneGraph/Object.h"

// GameEngine
#include "Utils.hh"


#include "GraphicsComponent.hh"


GameEngine::GraphicsComponent::GraphicsComponent(GameEngine::GameObject& owner,
        GameEngine::Object3D& magnumObject)
    : Component(owner),
    magnumObject_(&magnumObject)
{
}

GameEngine::GraphicsComponent::~GraphicsComponent() {
    delete magnumObject_;
}

void GameEngine::GraphicsComponent::update() {
    double x = owner_->position()->x;
    double y = owner_->position()->y;
    double z = owner_->position()->z;


    double w = owner_->orientation()->w;
    x = owner_->orientation()->x;
    y = owner_->orientation()->y;
    z = owner_->orientation()->z;
    /* Ogre::Quaternion quat(w, x, y, z); */
    /* node_->setOrientation(quat); */
}
