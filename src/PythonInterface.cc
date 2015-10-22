// std
#include <iostream>

// Boost
#include <boost/python.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/noncopyable.hpp>

// Magnum
#include <Magnum/Math/Vector3.h>
#include <Magnum/Math/Quaternion.h>

// GameEngine
#include "GameObject.hh"
#include "Logic.hh"


#include "PythonInterface.hh"


BOOST_PYTHON_MODULE(libGameEngine) {
    using namespace boost::python;

    // Magnum
    class_<Magnum::Quaternion>("Quaternion", init<Magnum::Quaternion>())
        .def(init<>())
        .def("rotation", &Magnum::Quaternion::rotation)
        .def("normalized", &Magnum::Quaternion::normalized)
        .def("isNormalized", &Magnum::Quaternion::isNormalized);
    class_<Magnum::Vector3>("Vector3", init<float, float, float>())
        .def("normalized", &Magnum::Vector3::normalized)
        .def("isNormalized", &Magnum::Vector3::isNormalized);
    class_<Magnum::Math::Rad<float>>("Rad", init<float>());

    // GameEngine
    class_<GameEngine::GameObject, boost::noncopyable>("GameObject", no_init)
        .def("translate", &GameEngine::GameObject::translate)
        .def("moveTo", &GameEngine::GameObject::moveTo)
        .def("rotate", &GameEngine::GameObject::rotate)
        .def("setOrientation", &GameEngine::GameObject::setOrientation);
    /* class_<GameEngine::Vector3>("Vector3", init<double, double, double>()) */
    /*     .def("normalize", &GameEngine::Vector3::normalize); */
    /* class_<GameEngine::Quaternion>("Quaternion", init<GameEngine::Vector3, double>()) */
    /*     .def(init<>()); */
    class_<GameEngine::Logic, boost::noncopyable>("Logic", no_init);
}
