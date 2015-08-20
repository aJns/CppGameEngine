#ifndef LOGIC_HH
#define LOGIC_HH

#include <memory>

#include <OgreSceneManager.h>

#include "GameObject.hh"

namespace GameEngine {
  class Logic
  {
  public:
    Logic(Ogre::SceneManager* sceneMgr);
    ~Logic();
    void runGameLoop();
    void setup(const bool& shutDown);
    void updateLogic();
    void processInput();
  private:

  private:
    std::shared_ptr<Ogre::SceneManager> sceneMgr_;
    /* std::shared_ptr<GameEngine::GameObject> gameObject_; */
    GameEngine::GameObject gameObject_;
    
    const bool* shutDown_;
  };
}

#endif // LOGIC_HH
