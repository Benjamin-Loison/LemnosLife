#ifndef VECTOR3D_H
#define VECTOR3D_H

#include <vector>

class Vector3D
{
    public:
        double X, Y, Z, length() const;
        Vector3D();
        Vector3D(double, double, double);
        Vector3D(std::vector<double>);
        Vector3D(const double coordinates[3]);
        Vector3D(const Vector3D &v);
        Vector3D(const Vector3D &from, const Vector3D &to);
        Vector3D &operator = (const Vector3D &v), &operator += (const Vector3D &v), operator + (const Vector3D &v) const, &operator -= (const Vector3D &v), operator - (const Vector3D &v) const, &operator *= (const double a), operator * (const double a)const, &operator /= (const double a), operator / (const double a) const, crossProduct(const Vector3D &v) const, &normalize();
        double dot(const Vector3D & v);
        bool operator !=(Vector3D const& a);
        friend Vector3D operator* (const double a, const Vector3D &v);
};

Vector3D moduloVector(Vector3D, double);

#endif
