#ifndef _PARTITIONING_H_INCLUDED
#define _PARTITIONING_H_INCLUDED

#include <vector>

struct Point
{
    Point();
    Point(double, double);
    double x,y;
};

struct Point3D
{
    Point3D();
    Point3D(double, double, double);
    double x,y,z;
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
    Point A,B,C,D;
    Segment AB, BC, CD, DA;
    std::vector<Segment> segments;
};

void initializePartition(int, int);
bool addObject(double, double, double, double);
std::vector<std::vector<Carre>> getMap();
void getMultipleIntersections(Segment, int, int);
int getMiddleX(), getMiddleY();
std::vector<std::pair<int, int>> getGrid();
OBB getOBBpartition();
void getMultipleOBBIntersections(Segment, int, int);

#endif // PARTITIONING_H_INCLUDED