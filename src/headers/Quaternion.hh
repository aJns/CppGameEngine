#ifndef QUATERNION_HH
#define QUATERNION_HH


namespace GameEngine {
    class Quaternion {
    public:
        double w;
        double x;
        double y;
        double z;

        Quaternion();
    private:
        void normalize(double unitTolerance);
    };
}

#endif // QUATERNION_HH
