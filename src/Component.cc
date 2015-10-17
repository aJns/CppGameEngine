#include "Component.hh"

GameEngine::Component::Component(GameEngine::GameObject& owner) {
    owner_ = &owner;
}

GameEngine::Component::~Component() {
}

void GameEngine::Component::update() {
}
