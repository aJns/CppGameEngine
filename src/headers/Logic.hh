#ifndef LOGIC_HH
#define LOGIC_HH

// std
#include <memory>
#include <string>
#include <vector>

// Boost
#include <boost/python.hpp>

// Ogre3D
#include <OgreSceneManager.h>

// GameEngine
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
    void runInitScript(std::string scriptName);
  private:

  private:
    std::shared_ptr<Ogre::SceneManager> sceneMgr_;
    std::shared_ptr<boost::python::object> pythonGlobal_;
    /* GameEngine::GameObject gameObject_; */
    std::vector<GameEngine::GameObject> objectVector_;
    
    const bool* shutDown_;
  };
}

#endif // LOGIC_HH
