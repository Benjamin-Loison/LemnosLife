#ifndef COLLISION_3D_H_INCLUDED
#define COLLISION_3D_H_INCLUDED

#include "Vector3D.h"
#include <string>

#define EPSILON 0.0000001
// recommanded value for Möller-Trumbore 0.0000001 (used to be 0.000000000000000001)

struct Point
{
    Point();
    Point(double, double);
    double x, y;
};

struct Segment
{
    Segment();
    Segment(Point, Point);
    Point A,B;
};

struct OBB
{
    Point A, B, C, D;
    Segment AB, BC, CD, DA;
    std::vector<Segment> segments;
};

bool rayPicking(Vector3D from, Vector3D to, Vector3D a, Vector3D b, Vector3D c, Vector3D d, Vector3D* intersectPoint), isCollided(OBB obb0, OBB obb1);
std::vector<Vector3D> getParts(std::string, std::string);
std::string getBodyPart(unsigned int bodyPartIndex);

#endif