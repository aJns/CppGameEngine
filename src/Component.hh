#ifndef COMPONENT_HH
#define COMPONENT_HH

#include <memory>

#include "GameObject.hh"

namespace GameEngine {
    class Component
    {
    public:
        Component(GameEngine::GameObject& owner);
        virtual ~Component();
        virtual void update();
    protected:
        std::shared_ptr<GameEngine::GameObject> owner_;
    };
}

#endif // COMPONENT_HH
