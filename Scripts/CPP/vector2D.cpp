#include "vector2d.h"
#include <cmath>
using namespace std;

Vector2D::Vector2D(Vector2D A, Vector2D B) : X(B.X - A.X), Y(B.Y - A.Y) {}

Vector2D::Vector2D(Vector3D A) : X(A.X), Y(A.Y) {}

double Vector2D::length() const
{
    return sqrt(X * X + Y * Y);
}

double determinant(Vector2D AB, Vector2D AP)
{
    return AB.X * AP.Y - AB.Y * AP.X;
}

double determinant(Vector2D A, Vector2D B, Vector2D P)
{
    return determinant(Vector2D(A, B), Vector2D(A, P));
}

Vector2D &Vector2D::operator += (const Vector2D &v)
{
    X += v.X;
    Y += v.Y;
    return *this;
}

Vector2D Vector2D::operator + (const Vector2D &v) const
{
    Vector2D t = *this;
    t += v;
    return t;
}
