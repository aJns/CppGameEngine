#include <iostream>

#include "Utils.hh"

void GameEngine::visibleMsg(std::string output) {
    std::cout << std::endl 
        << "**** **** **** **** **** **** **** **** **** **** **** **** ****"
        << std::endl;

    std::cout << output;

    std::cout << std::endl 
        << "**** **** **** **** **** **** **** **** **** **** **** **** ****"
        << std::endl;
}
