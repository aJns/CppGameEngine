// std
#include <cmath>
#include <iostream>


#include "Vector3.hh"


GameEngine::Vector3::Vector3(double x, double y, double z) 
    : x(x), y(y), z(z)
{
}

bool GameEngine::Vector3::isUnit(double unitTolerance) {
    double x2 = x*x;
    double y2 = y*y;
    double z2 = z*z;
    double magnitude = x2+y2+z2;
    return std::abs(1-magnitude) < unitTolerance;
}

void GameEngine::Vector3::normalize() {
    double magnitude = this->magnitude();
    x = x / magnitude;
    y = y / magnitude;
    z = z / magnitude;
}

double GameEngine::Vector3::magnitude() {
    double x2 = x*x;
    double y2 = y*y;
    double z2 = z*z;
    return std::sqrt(x2 + y2 + z2);
}

GameEngine::Vector3& GameEngine::Vector3::operator = (const GameEngine::Vector3& rhs) {
    x = rhs.x;
    y = rhs.y;
    z = rhs.y;

    return *this;
}

GameEngine::Vector3& GameEngine::Vector3::operator += (const GameEngine::Vector3& rhs) {
    x += rhs.x;
    y += rhs.y;
    z += rhs.y;

    return *this;
}
