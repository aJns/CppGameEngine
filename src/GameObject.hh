#ifndef GAMEOBJECT_HH
#define GAMEOBJECT_HH

// std
#include <string>

// Boost
#include <boost/python.hpp>

// GameEngine
#include "Vector3.hh"
#include "Quaternion.hh"
#include "ModelLoader.hh"


namespace GameEngine {
    class GraphicsComponent;
    class ScriptComponent;
    class GameObject
    {
    public:
        GameObject();
        ~GameObject();
        void update();

        void addGraphicsComponent(ModelLoader& modelLoader);
        void addScriptComponent(std::string scriptName, boost::python::object&
                pythonGlobal);

        const GameEngine::Vector3& position() const;
        void translate(GameEngine::Vector3 const& vector);
        void moveTo(GameEngine::Vector3 const& vector);

        const GameEngine::Quaternion& orientation() const;
        void rotate(GameEngine::Quaternion const& rotation);
        void setOrientation(GameEngine::Quaternion const& orientation);
    private:
        GameEngine::Vector3 position_;
        GameEngine::Quaternion orientation_;
        std::unique_ptr<GameEngine::GraphicsComponent> graphComp_;
        std::unique_ptr<GameEngine::ScriptComponent> scriptComp_;
    };
}

#endif // GAMEOBJECT_HH
