#ifndef COMPONENT_HH
#define COMPONENT_HH

#include "GameObject.hh"

namespace GameEngine {
  class Component
  {
  public:
    Component(GameEngine::GameObject owner);
  private:
    GameEngine::GameObject owner_;
  };
}

#endif // COMPONENT_HH
