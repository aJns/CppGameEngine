#ifndef LOGIC_HH
#define LOGIC_HH

// std
#include <memory>
#include <string>
#include <vector>

// Boost
#include <boost/python.hpp>
#include <boost/ptr_container/ptr_vector.hpp>

// GameEngine
#include "GameObject.hh"
#include "GameObjectFactory.hh"
#include "ModelLoader.hh"


namespace GameEngine {
  class Logic
  {
  public:
    Logic(ModelLoader* modelLoader);
    ~Logic();
    void setup();
    void update();
    void processInput();
    void runInitScript(std::string scriptName);

  private:
    std::unique_ptr<boost::python::object> pythonGlobal_;
    boost::ptr_vector<GameEngine::GameObject> objectVector_;
    std::unique_ptr<GameObjectFactory> objectFactory_;
  };
}


#endif // LOGIC_HH
