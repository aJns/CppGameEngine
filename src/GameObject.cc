#include "GameObject.hh"

// Need to include things here to work around circular dependencies
#include "GraphicsComponent.hh"


// TODO: Remove when done
#include <iostream>

GameEngine::GameObject::GameObject()
    : position_(0,0,0),
    graphComp_(nullptr)
{}

GameEngine::GameObject::~GameObject() {
    std::cout << "**** **** **** **** **** **** **** ****" << std::endl;

    std::cout << "Deleting GameObject" << std::endl;

    std::cout << "**** **** **** **** **** **** **** ****" << std::endl;

    if(graphComp_) {
        delete graphComp_;
    }
}

void GameEngine::GameObject::addGraphicsComponent(Ogre::SceneManager& sceneMgr) {
    /* graphComp_ = std::make_shared<GameEngine::GraphicsComponent> */
    /*     (GameEngine::GraphicsComponent(*this, sceneMgr)); */
    graphComp_ = new GameEngine::GraphicsComponent(*this, sceneMgr);
}

void GameEngine::GameObject::update() {
    if (graphComp_ != nullptr) {
        graphComp_->update();
    }
}

std::shared_ptr<Ogre::Vector3> const GameEngine::GameObject::position() const {
    return std::make_shared<Ogre::Vector3>(position_);
}

void GameEngine::GameObject::translate(Ogre::Vector3 const& vector) {
    position_ += vector;
}

void GameEngine::GameObject::moveTo(Ogre::Vector3 const& vector) {
    position_ = vector;
}
