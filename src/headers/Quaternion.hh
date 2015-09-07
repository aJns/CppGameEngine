#ifndef QUATERNION_HH
#define QUATERNION_HH

// GameEngine
#include "Vector3.hh"


namespace GameEngine {
    class Quaternion {
    public:
        double w;
        double x;
        double y;
        double z;

        Quaternion();
        Quaternion(double w, double x, double y, double z);
        Quaternion(GameEngine::Vector3 axis, double radAngle);

        bool isUnit(double unitTolerance);
        void normalize();
        double magnitude();

        // operators
        Quaternion operator * (const Quaternion& rhs) const;
    private:
    };
}

#endif // QUATERNION_HH
