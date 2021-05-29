#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <vector>

#include "../LemnosLife/Map/User/View.h"
#include "Vector3D.h"

struct point { double x; double y; };

class Vector2D
{
    public:
        double X, Y, length() const;
        Vector2D(double = 0, double = 0);
        Vector2D(std::vector<double>);
        Vector2D(const double coordinates[2]);
        Vector2D(Vector2D, Vector2D);
        Vector2D(Vector3D);
        Vector2D(View);
        Vector2D(Vector2D, View);
        void resize(double length);
        Vector2D &operator += (const Vector2D &v);
};

double determinant(Vector2D, Vector2D), determinant(Vector2D, Vector2D, Vector2D), distance(Vector2D, Vector2D);
Vector2D getVec2D(std::pair<double, double>);
std::vector<Vector2D> getVec2D(std::vector<std::pair<double, double>>);
Vector3D getVec3From2D(Vector2D vec2D);

#endif