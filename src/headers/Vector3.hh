#ifndef VECTOR3_HH
#define VECTOR3_HH


namespace GameEngine {
    class Vector3 {
    public:
        double x;
        double y;
        double z;

        Vector3(double x, double y, double z);

        bool isUnit(double unitTolerance);
        void normalize();
        double magnitude();

        // operators
        Vector3& operator = (const Vector3& rhs);
        Vector3& operator += (const Vector3& rhs);
    private:
    };
}

#endif // VECTOR3_HH
