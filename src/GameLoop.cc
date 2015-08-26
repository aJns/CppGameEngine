// std
#include <chrono>
#include <thread>

// Boost
#include <boost/python.hpp>

// GameEngine
#include "Utils.hh"

#include "GameLoop.hh"


void GameEngine::gameLoop(const bool& shutDown, GameEngine::Logic& gameLogic) {

    Py_Initialize();
    std::cout << "Using Python " << Py_GetVersion() << std::endl;

    const std::chrono::duration<double> TIME_PER_UPDATE(0.033);
    std::chrono::time_point<std::chrono::system_clock> previousTime,
        currentTime;
    std::chrono::duration<double> lag(0.0);
    previousTime = std::chrono::system_clock::now();
    while(!shutDown) {
        currentTime = std::chrono::system_clock::now();
        lag += (currentTime - previousTime);
        previousTime = currentTime;

        while (lag >= TIME_PER_UPDATE) {
            gameLogic.updateLogic();
            lag -= TIME_PER_UPDATE;

        }

        std::this_thread::sleep_for(TIME_PER_UPDATE - lag);


        try {
            GameEngine::visibleMsg("Executing script...");
            /* boost::python::exec_file("test.py"); */


            namespace python = boost::python;

            // Create the python environment
            python::object main = python::import("__main__");
            python::object global(main.attr("__dict__"));

            /* python::exec("print('hello world')", global, global); */
            python::object result = python::exec_file("test.py", global, global);
        }
        catch(...) {
            std::cout << "Python error!" << std::endl;
        }
    }
}
