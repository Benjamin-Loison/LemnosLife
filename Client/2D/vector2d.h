#ifndef VECTOR2D_H
#define VECTOR2D_H

#include "../3D/Render/Engine/vector3d.h"
#include <vector>
#include "../3D/Collision/partitioning.h"

struct point { double x; double y; };

class Vector2D
{
    public:
        double X, Y, length() const, quickLength() const;
        Vector2D(double = 0, double = 0);
        Vector2D(std::string, std::string);
        Vector2D(std::vector<double>);
        Vector2D(const double coordinates[2]);
        Vector2D(Vector2D, Vector2D);
        Vector2D(Vector3D);
        Vector2D(Point);
        Vector2D(std::string);
        void resize(double);
        bool operator ==(Vector2D const& a), operator !=(Vector2D const& a), isStriclySmallerThan(Vector2D const&) const;//, operator <(Vector2D const& a);
        std::string toString(std::string delimiter = " ");
        Vector2D &operator += (const Vector2D &v), operator + (const Vector2D &v) const;

        template <class Archive>
        void serialize(Archive& ar)
        {
            ar(X, Y);
        }
};

bool operator<(Vector2D const& a, Vector2D const& b);
double determinant(Vector2D, Vector2D), determinant(Vector2D, Vector2D, Vector2D);
Vector3D getVec3From2D(Vector2D vec2D); // if name getVec3 ambiguous calls...
//#include "../LemnosLife/Map/Position.h"
point resize(point, double);///, getPoint(Position), sumPoint(point, point);

#endif
