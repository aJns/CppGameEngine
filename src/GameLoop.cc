// std
#include <chrono>
#include <thread>
#include <iostream>

// GameEngine
#include "Utils.hh"


#include "GameLoop.hh"


void GameEngine::gameLoop(const bool& shutDown, GameEngine::Logic& gameLogic) {
    std::cout << "Looooping" << std::endl;
    int counter(0);


    const std::chrono::duration<double> TIME_PER_UPDATE(0.033);
    std::chrono::time_point<std::chrono::system_clock> previousTime,
        currentTime;
    std::chrono::duration<double> lag(0.0);
    previousTime = std::chrono::system_clock::now();
    while(!shutDown) {
        std::cout << "Loooop'd " << counter << " times" << std::endl;

        currentTime = std::chrono::system_clock::now();
        lag += (currentTime - previousTime);
        previousTime = currentTime;

        while (lag >= TIME_PER_UPDATE) {
            gameLogic.update();
            lag -= TIME_PER_UPDATE;

        }

        std::this_thread::sleep_for(TIME_PER_UPDATE - lag);

        counter++;
    }
}
