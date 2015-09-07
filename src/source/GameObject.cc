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
    if(graphComp_) {
        delete graphComp_;
    }
    if(scriptComp_) {
        delete scriptComp_;
    }
}

void GameEngine::GameObject::addGraphicsComponent(Ogre::SceneManager& sceneMgr) {
    graphComp_ = new GameEngine::GraphicsComponent(this, sceneMgr);
}

void GameEngine::GameObject::addScriptComponent(std::string scriptName, 
        boost::python::object& global) {
    scriptComp_ = new GameEngine::ScriptComponent(this, scriptName, global);
}

void GameEngine::GameObject::update() {
    if (graphComp_ != nullptr) {
        graphComp_->update();
    }
    if (scriptComp_ != nullptr) {
        scriptComp_->update();
    }
}

std::shared_ptr<GameEngine::Vector3> const GameEngine::GameObject::position() const {
    return std::make_shared<GameEngine::Vector3>(position_);
}

void GameEngine::GameObject::translate(GameEngine::Vector3 const& vector) {
    position_ += vector;
}

void GameEngine::GameObject::moveTo(GameEngine::Vector3 const& vector) {
    position_ = vector;
}

std::shared_ptr<GameEngine::Quaternion> const GameEngine::GameObject::orientation() const {
    return std::make_shared<GameEngine::Quaternion>(orientation_);
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
