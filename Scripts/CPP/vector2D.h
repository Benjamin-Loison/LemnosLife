#ifndef VECTOR2D_H
#define VECTOR2D_H

#include "vector3d.h"
#include <vector>

class Vector2D
{
    public:
        double X, Y, length() const;
        Vector2D(Vector2D, Vector2D);
        Vector2D(Vector3D);
        Vector2D &operator += (const Vector2D &v), operator + (const Vector2D &v) const;
};

double determinant(Vector2D, Vector2D), determinant(Vector2D, Vector2D, Vector2D);

#endif
