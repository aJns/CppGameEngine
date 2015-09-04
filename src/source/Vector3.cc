#include "Vector3.hh"

GameEngine::Vector3::Vector3(double x, double y, double z) 
    : x(x), y(y), z(z)
{
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

std::shared_ptr<Ogre::Vector3> const GameEngine::Vector3::getOgreVector() {
    return std::make_shared<Ogre::Vector3>(x, y, z);
}
