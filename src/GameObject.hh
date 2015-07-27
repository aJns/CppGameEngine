#ifndef GAMEOBJECT_HH
#define GAMEOBJECT_HH

#include <OgreVector3.h>

namespace GameEngine {
  class GameObject
  {
  public:
    Ogre::Vector3 position();
  private:
    Ogre::Vector3 position_;
  };
}

#endif // GAMEOBJECT_HH
