#include "Component.hh"

GameEngine::Component::Component(GameEngine::GameObject& owner) {
    owner_ = std::make_shared<GameEngine::GameObject>(owner);
}

