// std
#include <iostream>

// Boost
#include <boost/python.hpp>
#include <boost/make_shared.hpp>


#include "PythonInterface.hh"


boost::shared_ptr<Ogre::Vector3> GameEngine::python::createVector(double x,
        double y, double z) {
    std::cout << "Python module working!";
    return boost::make_shared<Ogre::Vector3>(x, y, z);
}

void GameEngine::python::testFunc() {
    std::cout << "Python module working!" << std::endl;
}

BOOST_PYTHON_MODULE(libGameEngine) {
    /* boost::python::def("createVector", GameEngine::python::createVector); */
    boost::python::def("testFunc", GameEngine::python::testFunc);
}
