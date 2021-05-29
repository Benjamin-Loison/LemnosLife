#ifndef VECTOR3D_H
#define VECTOR3D_H

#include <vector>
#include "../LemnosLife/Map/Position.h"

class Vector3D
{
    public:
        double X, Y, Z, length() const;
        Vector3D();
        Vector3D(double, double, double);
        Vector3D(std::string);
        Vector3D(std::vector<double>);
        Vector3D(const double coordinates[3]);
        Vector3D(Position);
        Vector3D(const Vector3D &v);
        Vector3D(const Vector3D &from, const Vector3D &to);
        Vector3D &operator = (const Vector3D &v), &operator += (const Vector3D &v), operator + (const Vector3D &v) const, &operator -= (const Vector3D &v), operator - (const Vector3D &v) const, &operator *= (const double a), operator * (const double a)const, &operator /= (const double a), operator / (const double a) const, crossProduct(const Vector3D &v) const, &normalize();
        double dot(const Vector3D & v); // why not naming it dotProduct like crossProduct ?
        bool operator !=(Vector3D const& a), operator ==(Vector3D const& a);
        friend Vector3D operator* (const double a, const Vector3D &v);
        void addX(double), addY(double), addZ(double);
        Vector3D setNorm(double norm);

        // don't have to include cereal O_o
        template <class Archive>
        void serialize(Archive& ar)
        {
            ar(X, Y, Z);
        }
};

Position getPositionFromVec3D(Vector3D);
Vector3D moduloVector(Vector3D, double);
double distance(Vector3D, Vector3D);
std::string toString(Vector3D, std::string = " ");

#endif
