#ifndef GRAPHICSCOMPONENT_HH
#define GRAPHICSCOMPONENT_HH

// GameEngine
#include "Component.hh"
#include "GameObject.hh"
#include "ModelLoader.hh"


namespace GameEngine {
    class GraphicsComponent : public GameEngine::Component 
    {
    public:
        GraphicsComponent(GameEngine::GameObject& owner,
                GameEngine::Object3D& magnumObject);
        virtual ~GraphicsComponent();
        virtual void update();
    private:
        GameEngine::Object3D* magnumObject_;
    };
}

#endif // GRAPHICSCOMPONENT_HH
