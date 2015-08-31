// Boost
#include <boost/python.hpp>

// GameEngine
#include "GraphicsComponent.hh"
#include "ScriptComponent.hh"
#include "Utils.hh"


#include "GameObject.hh"


GameEngine::GameObject::GameObject()
    : position_(0,0,0),
    graphComp_(nullptr)
{}

GameEngine::GameObject::~GameObject() {
    if(graphComp_) {
        delete graphComp_;
    }
    if(scriptComp_) {
        delete scriptComp_;
    }
}

void GameEngine::GameObject::addGraphicsComponent(Ogre::SceneManager& sceneMgr) {
    graphComp_ = new GameEngine::GraphicsComponent(this, sceneMgr);
}

void GameEngine::GameObject::addScriptComponent(std::string scriptName) {
    try {
        // Create the python environment
        boost::python::object main = boost::python::import("__main__");
        boost::python::object global(main.attr("__dict__"));

        scriptComp_ = new GameEngine::ScriptComponent(this, scriptName, global);
    }
    catch(...) {
        std::cout << "Python error!" << std::endl;
        PyErr_Print();
    }
}

void GameEngine::GameObject::update() {
    if (graphComp_ != nullptr) {
        graphComp_->update();
    }
    if (scriptComp_ != nullptr) {
        scriptComp_->update();
    }
}

std::shared_ptr<Ogre::Vector3> const GameEngine::GameObject::position() const {
    return std::make_shared<Ogre::Vector3>(position_);
}

void GameEngine::GameObject::translate(Ogre::Vector3 const& vector) {
    position_ += vector;
}

void GameEngine::GameObject::moveTo(Ogre::Vector3 const& vector) {
    position_ = vector;
}
