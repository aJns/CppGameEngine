#include "GameObjectFactory.hh"


GameEngine::GameObjectFactory::GameObjectFactory(ModelLoader& modelLoader,
        boost::python::object& pythonGlobal)
    : modelLoader_(&modelLoader),
    pythonGlobal_(&pythonGlobal)
{}

GameEngine::GameObjectFactory::~GameObjectFactory() {
}

GameEngine::GameObject* GameEngine::GameObjectFactory::createObject() {
    return new GameEngine::GameObject();
}
