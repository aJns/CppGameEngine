#ifndef GAMEOBJECT_HH
#define GAMEOBJECT_HH

// std
#include <string>

// Boost
#include <boost/python.hpp>

// GameEngine
#include "Vector3.hh"
#include "Quaternion.hh"


namespace GameEngine {
    class GraphicsComponent;
    class ScriptComponent;
    class GameObject
    {
    public:
        GameObject();
        ~GameObject();
        void addGraphicsComponent(GraphicsComponent& graphicsComponent);
        void addScriptComponent(ScriptComponent& scriptComponent);
        void update();
        std::shared_ptr<GameEngine::Vector3> const position() const;
        void translate(GameEngine::Vector3 const& vector);
        void moveTo(GameEngine::Vector3 const& vector);
        std::shared_ptr<GameEngine::Quaternion> const orientation() const;
        void rotate(GameEngine::Quaternion const& rotation);
        void setOrientation(GameEngine::Quaternion const& orientation);
    private:
        GameEngine::Vector3 position_;
        GameEngine::Quaternion orientation_;
        GameEngine::GraphicsComponent* graphComp_;
        GameEngine::ScriptComponent* scriptComp_;
    };
}

#endif // GAMEOBJECT_HH
