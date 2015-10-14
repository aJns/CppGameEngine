#ifndef SCRIPTCOMPONENT_HH
#define SCRIPTCOMPONENT_HH

// std
#include <string>

// Boost
#include <boost/python.hpp>

// GameEngine
#include "Component.hh"
#include "GameObject.hh"


namespace GameEngine {
    class ScriptComponent : public GameEngine::Component
    {
    public:
        ScriptComponent(GameEngine::GameObject& owner, std::string scriptName,
                boost::python::object global);
        virtual ~ScriptComponent();
        virtual void update();
    private:
        boost::python::object script_;
    };
}

#endif // SCRIPTCOMPONENT_HH
