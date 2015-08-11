#ifndef LOGIC_HH
#define LOGIC_HH

#include <memory>

#include <OgreSceneManager.h>

namespace GameEngine {
  class Logic
  {
  public:
    Logic(Ogre::SceneManager* sceneMgr);
    ~Logic();
    void runGameLoop();
    void setup();
  private:
    void updateLogic();
    void processInput();

  private:
    std::shared_ptr<Ogre::SceneManager> sceneMgr_;
  };
}

#endif // LOGIC_HH
