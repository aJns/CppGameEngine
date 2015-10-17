// GameEngine
#include "GraphicsComponent.hh"
#include "ScriptComponent.hh"

#include "GameObjectFactory.hh"


GameEngine::GameObjectFactory::GameObjectFactory(ModelLoader& modelLoader,
        boost::python::object& pythonGlobal)
    : modelLoader_(&modelLoader),
    pythonGlobal_(&pythonGlobal)
{}

GameEngine::GameObjectFactory::~GameObjectFactory() {
}

GameEngine::GameObject* GameEngine::GameObjectFactory::createObject() {
    GameEngine::GameObject* object = new GameEngine::GameObject();
    GameEngine::GraphicsComponent* graphComp = new
        GameEngine::GraphicsComponent(*object,
                *modelLoader_->loadModel("scene.ogex"));
    GameEngine::ScriptComponent* scriptComp = new
        GameEngine::ScriptComponent(*object, "test", *pythonGlobal_);
    object->addScriptComponent(*scriptComp);
    object->addGraphicsComponent(*graphComp);
    return object;
}
