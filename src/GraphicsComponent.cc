// std
#include <iostream>

// Corrade
#include <Corrade/Utility/Debug.h>

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
}

GameEngine::GraphicsComponent::~GraphicsComponent() {
    if(graphicsObject_) { delete graphicsObject_; }
}

void GameEngine::GraphicsComponent::update() {
    if(owner_->orientation().axis().normalized().isNormalized()) {
        Magnum::Matrix4 transform =
            Magnum::Matrix4::translation(owner_->position()) *
            Magnum::Matrix4::rotation(owner_->orientation().angle(),
                    owner_->orientation().axis().normalized());
        graphicsObject_->setTransformation(transform);
    } 
    else {
        std::cout << "Graphics object transformation error! ";
        std::cout << "Rotation vector isn't normalized"
        << std::endl;
    }
}
