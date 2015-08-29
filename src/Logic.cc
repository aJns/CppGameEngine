// std
#include <thread>

// Boost
#include <boost/python.hpp>

// Ogre3D
#include <OgreVector3.h>

// GameEngine
#include "GameObject.hh"
#include "GameLoop.hh"
#include "Utils.hh"

#include "Logic.hh"


GameEngine::Logic::Logic(Ogre::SceneManager* sceneMgr) 
    : sceneMgr_(sceneMgr),
    /* gameObject_(nullptr), */
    gameObject_(),
    shutDown_(nullptr)
{}

GameEngine::Logic::~Logic() {
}

void GameEngine::Logic::runGameLoop() {
    if(shutDown_ == nullptr) {
        return;
    }

    GameEngine::visibleMsg("running loop...");
}

void GameEngine::Logic::setup(const bool& shutDown) {
    shutDown_ = &shutDown;
    /* gameObject_ = std::make_shared<GameEngine::GameObject>(); */
    /* gameObject_->addGraphicsComponent(*sceneMgr_); */
    gameObject_.addGraphicsComponent(*sceneMgr_);

    Py_Initialize();
    std::cout << "Using Python " << Py_GetVersion() << std::endl;
}

void GameEngine::Logic::updateLogic() {
    Ogre::Vector3 vector(0.10, 0, 0);
    gameObject_.translate(vector);
    gameObject_.update();



    try {
        // Create the python environment
        boost::python::object main = boost::python::import("__main__");
        boost::python::object global(main.attr("__dict__"));

        boost::python::object result =
            boost::python::exec_file("./scripts/test.py", global, global);
    }
    catch(...) {
        std::cout << "Python error!" << std::endl;
        PyErr_Print();
    }
}

void GameEngine::Logic::processInput() {
}


