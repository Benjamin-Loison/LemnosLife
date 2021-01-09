#include "vector3d.h"
#include "utils.h"
#include <cmath>
using namespace std;

Vector3D::Vector3D() : X(0), Y(0), Z(0) {}

Vector3D::Vector3D(double x, double y, double z) : X(x), Y(y), Z(z) {}

Vector3D::Vector3D(vector<double> coordinates) : X(coordinates[0]), Y(coordinates[1]), Z(coordinates[2]) {}

Vector3D::Vector3D(const Vector3D &from, const Vector3D &to) : X(to.X - from.X), Y(to.Y - from.Y), Z(to.Z - from.Z) {}

string toString(Vector3D v)
{
	return to_string(v.X) + " " + to_string(v.Y) + " " + to_string(v.Z);
}

Vector3D &Vector3D::operator = (const Vector3D &v)
{
    X = v.X;
    Y = v.Y;
    Z = v.Z;
    return *this;
}

Vector3D &Vector3D::operator += (const Vector3D &v)
{
    X += v.X;
    Y += v.Y;
    Z += v.Z;
    return *this;
}

Vector3D Vector3D::operator + (const Vector3D &v) const
{
    Vector3D t = *this;
    t += v;
    return t;
}

Vector3D &Vector3D::operator -= (const Vector3D &v)
{
    X -= v.X;
    Y -= v.Y;
    Z -= v.Z;
    return *this;
}

Vector3D Vector3D::operator - (const Vector3D &v) const
{
    Vector3D t = *this;
    t -= v;
    return t;
}

Vector3D &Vector3D::operator *= (const double a)
{
    X *= a;
    Y *= a;
    Z *= a;
    return *this;
}

Vector3D Vector3D::operator * (const double a) const
{
    Vector3D t = *this;
    t *= a;
    return t;
}

Vector3D operator * (const double a, const Vector3D &v)
{
    return Vector3D(v.X * a, v.Y * a, v.Z * a);
}

Vector3D &Vector3D::operator /= (const double a)
{
    X /= a;
    Y /= a;
    Z /= a;
    return *this;
}

Vector3D Vector3D::operator / (const double a) const
{
    Vector3D t = *this;
    t /= a;
    return t;
}

double Vector3D::length() const
{
    return sqrt(X * X + Y * Y + Z * Z);
}

Vector3D moduloVector(Vector3D vec, double modulo)
{
    return Vector3D(remainderEuclidianDivisionStrict(vec.X, modulo), remainderEuclidianDivisionStrict(vec.Y, modulo), vec.Z);
}

double distance(Vector3D from, Vector3D to)
{
    return Vector3D(from, to).length();
}
