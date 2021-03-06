#ifndef PYTHONINTERFACE_HH
#define PYTHONINTERFACE_HH

// Boost
#include <boost/shared_ptr.hpp>

// Ogre
#include <OgreVector3.h>


namespace GameEngine {
    namespace python {
        boost::shared_ptr<Ogre::Vector3> createVector(double x, double y,
                double z);
        void testFunc();
    }
}

#endif // PYTHONINTERFACE_HH
