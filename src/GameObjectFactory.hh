#ifndef GAMEOBJECTFACTORY_HH
#define GAMEOBJECTFACTORY_HH


// std
#include <vector>
#include <memory>

// Boost
#include <boost/python.hpp>
#include <boost/ptr_container/ptr_vector.hpp>

// GameEngine
#include "GameObject.hh"
#include "ModelLoader.hh"


namespace GameEngine {
    class GameObjectFactory {
    public:
        GameObjectFactory(ModelLoader* modelLoader,
                boost::python::object* pythonGlobal);
        ~GameObjectFactory();
        
        void createObject(boost::ptr_vector<GameObject>& objectVector);
    private:
        ModelLoader* modelLoader_;
        boost::python::object* pythonGlobal_;
    };
}


#endif
