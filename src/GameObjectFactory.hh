#ifndef GAMEOBJECTFACTORY_HH
#define GAMEOBJECTFACTORY_HH


// std
#include <vector>
#include <memory>

// Boost
#include <boost/python.hpp>

// GameEngine
#include "GameObject.hh"
#include "ModelLoader.hh"


namespace GameEngine {
    class GameObjectFactory {
    public:
        GameObjectFactory(ModelLoader& modelLoader,
                boost::python::object& pythonGlobal);
        ~GameObjectFactory();
        
        GameObject* createObject();
    private:
        std::unique_ptr<ModelLoader> modelLoader_;
        std::shared_ptr<boost::python::object> pythonGlobal_;
    };
}


#endif
