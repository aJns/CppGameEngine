// std
#include <cmath>


#include "Quaternion.hh"


GameEngine::Quaternion::Quaternion()
    : w(1), x(0), y(0), z(0)
{}

GameEngine::Quaternion::Quaternion(double w, double x, double y, double z)
    : w(w), x(x), y(y), z(z)
{}

GameEngine::Quaternion::Quaternion(GameEngine::Vector3 unitAxis, double radAngle) {
    w = std::cos(radAngle/2);
    x = unitAxis.x * std::sin(radAngle/2);
    y = unitAxis.y * std::sin(radAngle/2);
    z = unitAxis.z * std::sin(radAngle/2);
}

bool GameEngine::Quaternion::isUnit(double unitTolerance) {
    double w2 = w*w;
    double x2 = x*x;
    double y2 = y*y;
    double z2 = z*z;
    double magnitude = w2+x2+y2+z2;
    return std::abs(1-magnitude) < unitTolerance;
}

double GameEngine::Quaternion::magnitude() {
    double w2 = w*w;
    double x2 = x*x;
    double y2 = y*y;
    double z2 = z*z;
    return sqrt(w2+x2+y2+z2);
}

GameEngine::Quaternion GameEngine::Quaternion::operator * (const 
        GameEngine::Quaternion& rhs) const {
    GameEngine::Quaternion product(1,0,0,0);

    product.w = this->w*rhs.w - this->x*rhs.x - this->y*rhs.y - this->z*rhs.z;
    product.x = this->w*rhs.x + this->x*rhs.w + this->y*rhs.z - this->z*rhs.y;
    product.y = this->w*rhs.y - this->x*rhs.z + this->y*rhs.w + this->z*rhs.x;
    product.z = this->w*rhs.z + this->x*rhs.y - this->y*rhs.x + this->z*rhs.w;

    return product;
}

void GameEngine::Quaternion::normalize() {
    double magnitude = this->magnitude();
    w = w / magnitude;
    x = x / magnitude;
    y = y / magnitude;
    z = z / magnitude;
}
