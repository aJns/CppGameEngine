// std
#include <thread>
#include <iostream>

// Boost
#include <boost/python.hpp>
#include <boost/shared_ptr.hpp>

// GameEngine
#include "GameObject.hh"
#include "GameLoop.hh"
#include "Utils.hh"


#include "Logic.hh"


GameEngine::Logic::Logic() 
    : objectVector_{}
{
    Py_Initialize();
    std::cout << "Using Python " << Py_GetVersion() << std::endl;
    
    try {
        // Create the python environment
        boost::python::object main = boost::python::import("__main__");
        /* boost::python::object global(main.attr("__dict__")); */
        pythonGlobal_= new boost::python::object(main.attr("__dict__"));
    }
    catch(...) {
        std::cout << "Python error! " << "Couldn't setup Python environment!"
            << std::endl;
        PyErr_Print();
    }
}

GameEngine::Logic::~Logic() {
    for (auto object : objectVector_) {
        delete object;
    }
}

void GameEngine::Logic::setup() {
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
        boost::python::object result = boost::python::exec_file(filenameStr,
                *pythonGlobal_, *pythonGlobal_);
        boost::python::object init = (*pythonGlobal_)["init"];
        /* init(boost::ref(*this)); */
        init();
    }
    catch(...) {
        std::cout << "Python error!" << std::endl;
        PyErr_Print();
    }
}
