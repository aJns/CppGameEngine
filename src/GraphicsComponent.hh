#ifndef GRAPHICSCOMPONENT_HH
#define GRAPHICSCOMPONENT_HH

#include <memory>
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreEntity.h>

#include "Component.hh"
#include "GameObject.hh"

namespace GameEngine {
    class GraphicsComponent : public GameEngine::Component 
    {
    public:
        GraphicsComponent(GameEngine::GameObject& owner, 
                Ogre::SceneManager& sceneMgr);
        ~GraphicsComponent();
        std::shared_ptr<Ogre::SceneNode> getNode();
        virtual void update();
    private:
        std::shared_ptr<Ogre::SceneNode> node_;
    };
}

#endif // GRAPHICSCOMPONENT_HH
