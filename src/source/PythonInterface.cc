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


#include "PythonInterface.hh"


BOOST_PYTHON_MODULE(libGameEngine) {
    using namespace boost::python;

    // Ogre3D
    /* class_<Ogre::Vector3>("Vector3", init<Ogre::Real,Ogre::Real,Ogre::Real>()); */

    // GameEngine
    class_<GameEngine::GameObject, boost::noncopyable>("GameObject", no_init)
        .def("translate", &GameEngine::GameObject::translate);
    class_<GameEngine::Vector3>("Vector3", init<double, double, double>());
}
