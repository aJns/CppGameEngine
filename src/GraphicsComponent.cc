// std
#include <iostream>

// Magnum
#include <Magnum/Math/Vector3.h>
#include <Magnum/Math/Matrix3.h>
#include <Magnum/Math/Matrix4.h>
#include <Magnum/Math/Quaternion.h>

// GameEngine
#include "Utils.hh"


#include "GraphicsComponent.hh"


GameEngine::GraphicsComponent::GraphicsComponent(GameEngine::GameObject* owner,
        GameEngine::ModelLoader& modelLoader)
    : Component(owner)
{
    graphicsObject_ = new Object3D{modelLoader.getScene()};
    modelLoader.loadModel(graphicsObject_, "scene.ogex");
    graphicsObject_->rotateX(Magnum::Rad(1.5));
}

GameEngine::GraphicsComponent::~GraphicsComponent() {
    if(graphicsObject_) { delete graphicsObject_; }
}

void GameEngine::GraphicsComponent::update() {
    float x = owner_->position().x;
    float y = owner_->position().y;
    float z = owner_->position().z;

    Magnum::Vector3 vector(x, y, z);

    graphicsObject_->setTransformation(Magnum::Matrix4::translation(vector));
}
