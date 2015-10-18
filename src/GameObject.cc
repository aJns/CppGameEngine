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

const GameEngine::Vector3& GameEngine::GameObject::position() const {
    return position_;
}

void GameEngine::GameObject::translate(GameEngine::Vector3 const& vector) {
    position_ += vector;
}

void GameEngine::GameObject::moveTo(GameEngine::Vector3 const& vector) {
    position_ = vector;
}

const GameEngine::Quaternion& GameEngine::GameObject::orientation() const {
    return orientation_;
}

void GameEngine::GameObject::rotate(GameEngine::Quaternion const& rotation) {
    orientation_ = rotation * orientation_;

    if(!orientation_.isUnit(0.01)) {
        orientation_.normalize();
    }
}

void GameEngine::GameObject::setOrientation(GameEngine::Quaternion const& orientation) {
    orientation_ = orientation;
}
