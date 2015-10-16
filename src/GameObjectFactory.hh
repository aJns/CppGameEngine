#ifndef GAMEOBJECTFACTORY_HH
#define GAMEOBJECTFACTORY_HH


// std
#include <vector>
#include <memory>

// Boost
#include <boost/python.hpp>

// GameEngine
#include "GameObject.hh"


namespace GameEngine {
    class GameObjectFactory {
    public:
        GameObjectFactory(std::vector<GameObject*>& objectVector,
                boost::python::object& pythonGlobal);
        
        void createObject();
    private:
        std::vector<GameObject*>* objectVector_;
        std::shared_ptr<boost::python::object> pythonGlobal_;
    };
}


#endif
