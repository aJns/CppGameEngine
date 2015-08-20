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
        void addGraphicsComponent(Ogre::SceneManager& sceneMgr);
        void update();
        std::shared_ptr<Ogre::Vector3> const position() const;
        void translate(Ogre::Vector3 const& vector);
        void moveTo(Ogre::Vector3 const& vector);
    private:
        Ogre::Vector3 position_;
        /* std::shared_ptr<GameEngine::GraphicsComponent> graphComp_; */
        GameEngine::GraphicsComponent* graphComp_;
    };
}

#endif // GAMEOBJECT_HH
