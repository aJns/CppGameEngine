#ifndef GRAPHICSCOMPONENT_HH
#define GRAPHICSCOMPONENT_HH


// std
#include <memory>

// GameEngine
#include "Component.hh"
#include "GameObject.hh"
#include "ModelLoader.hh"


namespace GameEngine {
    class GraphicsComponent : public GameEngine::Component 
    {
    public:
        GraphicsComponent(GameEngine::GameObject& owner,
                Object3D& graphicsObject);
        virtual ~GraphicsComponent();
        virtual void update();
    private:
        std::unique_ptr<Object3D> graphicsObject_;
    };
}

#endif // GRAPHICSCOMPONENT_HH
