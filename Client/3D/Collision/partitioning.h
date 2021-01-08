#ifndef PARTITIONING_H_INCLUDED
#define PARTITIONING_H_INCLUDED

#include <vector>
//#include "../../2D/vector2d.h"

struct Point
{
    Point();
    Point(double, double);
    //Point(Vector2D);
    double x, y;
};

struct Point3D
{
    Point3D();
    Point3D(double, double, double);
    double x, y, z;
};

struct Vector
{
    Vector(Point, Point);
    double x,y;
};

struct Segment
{
    Segment();
    Segment(Point, Point);
    Point A,B;
};

struct Carre  // un carre contient une liste (ou tableau) de segments
{
  std::vector<Segment> tableau;
};

struct OBB
{
    Point A, B, C, D;
    Segment AB, BC, CD, DA;
    std::vector<Segment> segments;
};

#include "../Render/Engine/vector3d.h"

void initializePartition(int, int), getMultipleOBBIntersections(Segment, int, int), getMultipleIntersections(Segment, int, int), computeSegments(OBB*);
bool addObject(double, double, double, double), isCollided(OBB, OBB);
std::vector<std::vector<Carre>> getMap();
int getMiddleX(), getMiddleY();
std::vector<std::pair<int, int>> getGrid();
OBB getOBBpartition();
std::string toString(Segment);

#endif
