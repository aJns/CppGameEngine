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


GameEngine::GraphicsComponent::GraphicsComponent(GameEngine::GameObject& owner,
        GameEngine::Object3D& graphicsObject)
    : Component(owner),
    graphicsObject_(&graphicsObject)
{
}

GameEngine::GraphicsComponent::~GraphicsComponent() {
}

void GameEngine::GraphicsComponent::update() {
    double x = owner_->position()->x;
    double y = owner_->position()->y;
    double z = owner_->position()->z;
    Magnum::Vector3 posVect(x, y, z);

    std::cout << x << y << z << std::endl;


    double w = owner_->orientation()->w;
    x = owner_->orientation()->x;
    y = owner_->orientation()->y;
    z = owner_->orientation()->z;
    Magnum::Vector3 rotVect(x, y, z);
    Magnum::Quaternion quat(rotVect, w);
    Magnum::Matrix3 rotMatrix(quat.toMatrix());

    graphicsObject_->transform(Magnum::Matrix4::from(rotMatrix, posVect));

    std::cout << x << y << z << w << std::endl;
}
