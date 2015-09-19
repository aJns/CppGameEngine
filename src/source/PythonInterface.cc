// std
#include <iostream>

// Boost
#include <boost/python.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/noncopyable.hpp>

// Ogre3D

// GameEngine
#include "GameObject.hh"
#include "Vector3.hh"
#include "Logic.hh"


#include "PythonInterface.hh"


BOOST_PYTHON_MODULE(libGameEngine) {
    using namespace boost::python;

    // Ogre3D
    /* class_<Ogre::Vector3>("Vector3", init<Ogre::Real,Ogre::Real,Ogre::Real>()); */

    // GameEngine
    class_<GameEngine::GameObject, boost::noncopyable>("GameObject", no_init)
        .def("translate", &GameEngine::GameObject::translate)
        .def("rotate", &GameEngine::GameObject::rotate)
        .def("setOrientation", &GameEngine::GameObject::setOrientation);
    class_<GameEngine::Vector3>("Vector3", init<double, double, double>())
        .def("normalize", &GameEngine::Vector3::normalize);
    class_<GameEngine::Quaternion>("Quaternion", init<GameEngine::Vector3, double>())
        .def(init<>());
    class_<GameEngine::Logic>("Logic", no_init);
}
