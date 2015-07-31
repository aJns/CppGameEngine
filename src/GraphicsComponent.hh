#ifndef GRAPHICSCOMPONENT_HH
#define GRAPHICSCOMPONENT_HH

#include<memory>
#include <OgreSceneNode.h>

#include "Component.hh"

namespace GameEngine {
    class GraphicsComponent : public Component
    {
    public:
        GraphicsComponent(GameEngine::GameObject owner);
        ~GraphicsComponent();
        std::shared_ptr<Ogre::SceneNode> getNode();
    };
}

#endif // GRAPHICSCOMPONENT_HH
