#ifndef MATH_PLUS_H_INCLUDED
#define MATH_PLUS_H_INCLUDED

#include <cmath>
#include <math.h>
#include "../3D/Render/Engine/vector3d.h"
#include "../LemnosLife/Map/ViewAngle.h"
#include "../LemnosLife/Map/Position.h"
// why here and not in cpp file ?
#include <string>
#include "../2D/vector2d.h"

// The following define isn't required on every plateform
#define M_PI 3.14159265358979323846
#define UNSIGNED_SHORT_MAX 65535
#define UNSIGNED_INT_MAX 4294967295

const double PI_DIVIDED_BY_2 = M_PI / 2, OPPOSITE_PI_DIVIDED_BY_2 = -PI_DIVIDED_BY_2;

struct line {double a; double b;};

class Matrix
{
    public:
        Matrix();
        Matrix(Vector3D);
        Matrix(unsigned short, unsigned short);
        Matrix product(Matrix), transpose();
        unsigned short getN(), getP();
        void set(unsigned short i, unsigned short j, double value);
        double get(unsigned short i, unsigned short j);
        std::string toString();
        Vector3D toVec3D();
    private:
        unsigned short m_n, m_p;
        std::vector<std::vector<double>> m_data;
};

point getIntersection(line, line), rotate(point, double = PI_DIVIDED_BY_2), rotate(point, point, double = PI_DIVIDED_BY_2), getMiddle(point, point), rotateResize(point, point, double, double), getPoint(Vector2D), reverse(point);
bool isInteger(double), isLine(double, double), isIntersection(line, line);
line getLine(double, double, double, double), getLine(point, point);
int absolute(int);
double remainderEuclidianDivision(double, double), remainderEuclidianDivisionStrict(double, double), distance(double, double, double, double), distance(double, double, double, double, double, double), distance(point, point), min(double, double), min(double, double, double, double), max(double, double),
       max(double, double, double, double), getRadians(double), cosDeg(double), sinDeg(double), compute(std::string str), getDegrees(double radians);
long timeIn(double, double), integerDivision(double, double), integerIn(double, double), timeInStrict(double, double);
Vector2D getVector2D(point); // why point and Vector2D both exist ?
std::pair<double, double> solveSystem2Equations2Unknowns(Vector2D, Vector2D, Vector2D);
Vector3D rotate(Vector3D, double), rotate(Vector3D, double theta, double phi, double roll), rotate(Position pointToRotate, ViewAngle viewAngle);

#endif
