// std
#include <iostream>

// GameEngine
#include "GraphicsComponent.hh"
#include "ScriptComponent.hh"

#include "GameObjectFactory.hh"


GameEngine::GameObjectFactory::GameObjectFactory(ModelLoader* modelLoader,
        boost::python::object* pythonGlobal)
    : modelLoader_(modelLoader),
    pythonGlobal_(pythonGlobal)
{}

GameEngine::GameObjectFactory::~GameObjectFactory() {
}

void
GameEngine::GameObjectFactory::createObject(boost::ptr_vector<GameEngine::GameObject>&
        objectVector) {
    objectVector.push_back(new GameEngine::GameObject());
    objectVector.back().addGraphicsComponent(*modelLoader_);
    objectVector.back().addScriptComponent("test", *pythonGlobal_);
}
