#ifndef GAMEOBJECT_HH
#define GAMEOBJECT_HH

// std
#include <string>

// Boost
#include <boost/python.hpp>

// Ogre3D
#include <OgreSceneManager.h>

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
        void addGraphicsComponent(Ogre::SceneManager& sceneMgr);
        void addScriptComponent(std::string scriptName, 
                boost::python::object& global);
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
