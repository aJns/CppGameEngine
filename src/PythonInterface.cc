// std
#include <iostream>

// Boost
#include <boost/python.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/noncopyable.hpp>

// Ogre3D
#include <OgreVector3.h>

// GameEngine
#include "GameObject.hh"


#include "PythonInterface.hh"


void GameEngine::python::testFunc() {
    std::cout << "Python module working!" << std::endl;
}

BOOST_PYTHON_MODULE(libGameEngine) {
    using namespace boost::python;

    // Tests
    boost::python::def("testFunc", GameEngine::python::testFunc);

    // Ogre3D
    class_<Ogre::Vector3>("Vector3", init<Ogre::Real,Ogre::Real,Ogre::Real>());

    // GameEngine
    class_<GameEngine::GameObject, boost::shared_ptr<GameEngine::GameObject>, boost::noncopyable>("GameObject", no_init)
        .def("translate", &GameEngine::GameObject::translate);
}
