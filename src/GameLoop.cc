// std
#include <chrono>
#include <thread>

// GameEngine
#include "Utils.hh"

#include "GameLoop.hh"


void GameEngine::gameLoop(const bool& shutDown, GameEngine::Logic& gameLogic) {
    GameEngine::visibleMsg("gameLoop'd");
    while(!shutDown) {
        gameLogic.updateLogic();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}
