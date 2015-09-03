#ifndef GAMEOBJECT_HH
#define GAMEOBJECT_HH

// std
#include <string>

// Boost
#include <boost/python.hpp>

// Ogre3D
#include <OgreVector3.h>
#include <OgreSceneManager.h>


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
        std::shared_ptr<Ogre::Vector3> const position() const;
        void translate(Ogre::Vector3 const& vector);
        void moveTo(Ogre::Vector3 const& vector);
    private:
        Ogre::Vector3 position_;
        GameEngine::GraphicsComponent* graphComp_;
        GameEngine::ScriptComponent* scriptComp_;
    };
}

#endif // GAMEOBJECT_HH
