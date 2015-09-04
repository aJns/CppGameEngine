#ifndef VECTOR3_HH
#define VECTOR3_HH

// std
#include <memory>

// Ogre3D
#include <OgreVector3.h>


namespace GameEngine {
    class Vector3 {
    public:
        Vector3(double x, double y, double z);
        double x;
        double y;
        double z;

        // operators
        Vector3& operator = (const Vector3& rhs);
        Vector3& operator += (const Vector3& rhs);

        std::shared_ptr<Ogre::Vector3> const getOgreVector();
    private:
    };
}

#endif // VECTOR3_HH
