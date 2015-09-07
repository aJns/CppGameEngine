// std
#include <cmath>


#include "Quaternion.hh"


GameEngine::Quaternion::Quaternion()
    : w(1), x(0), y(0), z(0)
{
}

// Normalizes the Quaternion, IF it's outside the tolerance
void GameEngine::Quaternion::normalize(double unitTolerance) {
    double w2 = w*w;
    double x2 = x*x;
    double y2 = y*y;
    double z2 = z*z;
    double magnitude = w2+x2+y2+z2;
    if(std::abs(1-magnitude) > unitTolerance) {
        magnitude = std::sqrt(magnitude);
        w = w / magnitude;
        x = x / magnitude;
        y = y / magnitude;
        z = z / magnitude;
    }
}
