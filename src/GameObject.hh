#ifndef GAMEOBJECT_HH
#define GAMEOBJECT_HH

#include <memory>
#include <OgreVector3.h>
#include <OgreSceneManager.h>

namespace GameEngine {
    class GraphicsComponent;
    class GameObject
    {
    public:
        GameObject();
        ~GameObject();
        std::shared_ptr<Ogre::Vector3> position();
        void addGraphicsComponent(Ogre::SceneManager& sceneMgr);
    private:
        Ogre::Vector3 position_;
        std::shared_ptr<GameEngine::GraphicsComponent> graphComp_;
    };
}

#endif // GAMEOBJECT_HH
