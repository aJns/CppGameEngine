#ifndef GAMEOBJECT_HH
#define GAMEOBJECT_HH

// std
#include <string>

// Boost
#include <boost/python.hpp>

// Magnum
#include <Magnum/Math/Vector3.h>
#include <Magnum/Math/Quaternion.h>

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

        const Magnum::Vector3& position() const;
        void translate(Magnum::Vector3 const& vector);
        void moveTo(Magnum::Vector3 const& vector);

        const Magnum::Quaternion& orientation() const;
        void rotate(Magnum::Quaternion const& rotation);
        void setOrientation(Magnum::Quaternion const& orientation);
    private:
        Magnum::Vector3 position_;
        Magnum::Quaternion orientation_;
        std::unique_ptr<GameEngine::GraphicsComponent> graphComp_;
        std::unique_ptr<GameEngine::ScriptComponent> scriptComp_;
    };
}

#endif // GAMEOBJECT_HH
