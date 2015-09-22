// std
#include <thread>

// Boost
#include <boost/python.hpp>
#include <boost/shared_ptr.hpp>

// Ogre3D
#include <OgreVector3.h>

// GameEngine
#include "GameObject.hh"
#include "GameLoop.hh"
#include "Utils.hh"


#include "Logic.hh"


GameEngine::Logic::Logic(Ogre::SceneManager* sceneMgr) 
    : sceneMgr_(sceneMgr),
    objectVector_{},
    shutDown_(nullptr)
{}

GameEngine::Logic::~Logic() {
    for (auto object : objectVector_) {
        delete object;
    }
}

void GameEngine::Logic::runGameLoop() {
    if(shutDown_ == nullptr) {
        return;
    }

    GameEngine::visibleMsg("running loop...");
}

void GameEngine::Logic::setup(const bool& shutDown) {
    shutDown_ = &shutDown;

    Py_Initialize();
    std::cout << "Using Python " << Py_GetVersion() << std::endl;
    
    try {
        // Create the python environment
        boost::python::object main = boost::python::import("__main__");
        /* boost::python::object global(main.attr("__dict__")); */
        pythonGlobal_ = std::make_shared<boost::python::object>(main.attr("__dict__"));
    }
    catch(...) {
        std::cout << "Python error! " << "Couldn't setup Python environment!"
            << std::endl;
        PyErr_Print();
    }

    objectVector_.push_back(new GameEngine::GameObject());
    objectVector_.back()->addGraphicsComponent(*sceneMgr_);
    objectVector_.back()->addScriptComponent("test", *pythonGlobal_);

    objectVector_.push_back(new GameEngine::GameObject());
    GameEngine::Vector3 vektori(50, 0, 0);
    objectVector_.back()->translate(vektori);
    objectVector_.back()->addGraphicsComponent(*sceneMgr_);
    objectVector_.back()->addScriptComponent("test", *pythonGlobal_);
}

void GameEngine::Logic::updateLogic() {
    for (auto object : objectVector_) {
        object->update();
    }
}

void GameEngine::Logic::processInput() {
}

void GameEngine::Logic::runInitScript(std::string scriptName) {
    try {
        std::string filename("./scripts/");
        filename.append(scriptName);
        filename.append(".py");

        boost::python::str filenameStr(filename);
        boost::python::object result =
            boost::python::exec_file(filenameStr, *pythonGlobal_, *pythonGlobal_);
        boost::python::object init = (*pythonGlobal_)["init"];
        init(boost::ref(*this));
    }
    catch(...) {
        std::cout << "Python error!" << std::endl;
        PyErr_Print();
    }
}
