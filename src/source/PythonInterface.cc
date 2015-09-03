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


BOOST_PYTHON_MODULE(libGameEngine) {
    using namespace boost::python;

    // Ogre3D
    class_<Ogre::Vector3>("Vector3", init<Ogre::Real,Ogre::Real,Ogre::Real>());

    // GameEngine
    class_<GameEngine::GameObject, boost::noncopyable>("GameObject", no_init)
        .def("translate", &GameEngine::GameObject::translate);
}
