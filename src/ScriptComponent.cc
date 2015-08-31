#include "ScriptComponent.hh"


GameEngine::ScriptComponent::ScriptComponent(GameEngine::GameObject* owner,
        std::string scriptName, boost::python::object global)
    : Component(owner)
{
    try {
        std::string filename("./scripts/");
        filename.append(scriptName);
        filename.append(".py");

        boost::python::str filenameStr(filename);
        boost::python::object result =
            boost::python::exec_file(filenameStr, global, global);
        script_ = global["test"];
    }
    catch(...) {
        std::cout << "Python error!" << std::endl;
        PyErr_Print();
    }
}

void GameEngine::ScriptComponent::update() {
    try {
        if(!script_.is_none()) {
            script_(boost::ref(*owner_));
        } else {
            std::cout << "Script is null!" << std::endl;
        }
    }
    catch(...) {
        std::cout << "Python error!" << std::endl;
        PyErr_Print();
    }
}
