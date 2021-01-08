#ifndef VECTOR3D_H
#define VECTOR3D_H

#include <vector>
#include <string>

//#include "../../../LemnosLife/Map/Position.h"
#include <glm.hpp>
//#include "../../../2D/vector2d.h" - doesn't seem to work fine for constructor

class Vector3D
{
    public:
        double X, Y, Z, length() const;
        Vector3D();
        Vector3D(std::string, std::string delimiter = ";");
        Vector3D(double, double = 0, double = 0);
        Vector3D(std::vector<double>);
        Vector3D(const double coordinates[3]);
        Vector3D(const Vector3D &v);
        Vector3D(const Vector3D &from, const Vector3D &to);
        //Vector3D(Position); // use getVec3 instead
        Vector3D(glm::vec3);
        //Vector3D(Vector2D);
        Vector3D(glm::vec4); // test multitexturing
        //Vector3D(Point, double);

        //#include "../../../LemnosLife/Map/User/User.h" // why can't ?
        //Vector3D(User*);
        Vector3D &operator = (const Vector3D &v), &operator += (const Vector3D &v), operator + (const Vector3D &v) const, &operator -= (const Vector3D &v), operator - (const Vector3D &v) const, &operator *= (const double a), operator * (const double a)const, &operator /= (const double a), operator / (const double a) const, crossProduct(const Vector3D &v) const, &normalize();
        double dot(const Vector3D & v);
        bool operator !=(Vector3D const& a);
        friend Vector3D operator* (const double a, const Vector3D &v);
        Vector3D setNorm(double norm);
        //std::string toString(); // can't used it because of StringPlus function
};

//#include "../../Collision/partitioning.h"
// This file doesn't exist say CodeBlocks, but we can open by right-clicking and select Open and it is proposed by CodeBlocks as auto-completion, I conclude: CodeBlocks are you stupid ?

Vector3D moduloVector(Vector3D, double)/*, getVec3(Point point, double z)*/; // if in class bug of one in the other
//#include "../../../2D/vector2d.h"
double distance(Vector3D, Vector3D);//, distance(Vector2D, Vector2D);

/*#include "../../../LemnosLife/Map/User/ViewGravity.h"

glm::vec3 getVec3(ViewGravity*);*/

#endif
