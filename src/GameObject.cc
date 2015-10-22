// std
#include <iostream>

// Boost
#include <boost/python.hpp>

// GameEngine
#include "GraphicsComponent.hh"
#include "ScriptComponent.hh"
#include "Utils.hh"


#include "GameObject.hh"


GameEngine::GameObject::GameObject()
    : position_(0,0,0),
    orientation_(),
    graphComp_(nullptr),
    scriptComp_(nullptr)
{}

GameEngine::GameObject::~GameObject() {
}

void GameEngine::GameObject::addGraphicsComponent(GameEngine::ModelLoader&
        modelLoader) {
    graphComp_ = std::unique_ptr<GameEngine::GraphicsComponent>(new
            GameEngine::GraphicsComponent(this, modelLoader));
}

void GameEngine::GameObject::addScriptComponent(std::string scriptName,
        boost::python::object& pythonGlobal) {
    scriptComp_ = std::unique_ptr<GameEngine::ScriptComponent>(new
            GameEngine::ScriptComponent(this, scriptName, pythonGlobal));
}

void GameEngine::GameObject::update() {
    if (graphComp_) {
        graphComp_->update();
    }
    if (scriptComp_) {
        scriptComp_->update();
    }

    std::cout << "GameObject: " << this << " updated!" << std::endl;
}

const Magnum::Vector3& GameEngine::GameObject::position() const {
    return position_;
}

void GameEngine::GameObject::translate(Magnum::Vector3 const& vector) {
    position_ += vector;
}

void GameEngine::GameObject::moveTo(Magnum::Vector3 const& vector) {
    position_ = vector;
}

const Magnum::Quaternion& GameEngine::GameObject::orientation() const {
    return orientation_;
}

void GameEngine::GameObject::rotate(Magnum::Quaternion const& rotation) {
    if(rotation.axis().isNormalized()) {
        orientation_ = rotation * orientation_;
    } 
    else {
        std::cout << "Can't rotate, axis vector isn't normalized" << std::endl;
    }
}

void GameEngine::GameObject::setOrientation(Magnum::Quaternion const& orientation) {
    orientation_ = orientation;
}
