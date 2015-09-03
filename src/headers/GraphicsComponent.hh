#ifndef GRAPHICSCOMPONENT_HH
#define GRAPHICSCOMPONENT_HH

// Ogre3D
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreEntity.h>

// GameEngine
#include "Component.hh"
#include "GameObject.hh"


namespace GameEngine {
    class GraphicsComponent : public GameEngine::Component 
    {
    public:
        GraphicsComponent(GameEngine::GameObject* owner, 
                Ogre::SceneManager& sceneMgr);
        virtual ~GraphicsComponent();
        virtual void update();
    private:
        Ogre::SceneNode* node_;
    };
}

#endif // GRAPHICSCOMPONENT_HH
