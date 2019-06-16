#ifndef VECTOR2D_H
#define VECTOR2D_H

#include "../3D/Render/Engine/vector3d.h"
#include <vector>

class Vector2D
{
    public:
        double X, Y, length() const;
        Vector2D();
        Vector2D(double, double);
        Vector2D(std::vector<double>);
        Vector2D(const double coordinates[2]);
        Vector2D(Vector2D, Vector2D);
        Vector2D(Vector3D);
};

double determinant(Vector2D, Vector2D), determinant(Vector2D, Vector2D, Vector2D);

#endif
