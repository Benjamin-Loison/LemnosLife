#ifndef MATH_PLUS_H_INCLUDED
#define MATH_PLUS_H_INCLUDED

#include <cmath>
#include <math.h>
#include <string>

#include "../Collisions/Vector2D.h"
#include "../Collisions/Vector3D.h"

#define UNSIGNED_SHORT_MAX 65535
#define UNSIGNED_INT_MAX 4294967295
#define UNSIGNED_LONG_MAX 18446744073709551615

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
        double m_data[3][3];
};

double remainderEuclidianDivision(double, double), remainderEuclidianDivisionStrict(double, double), compute(std::string str), getRadians(double), getDegrees(double), cosDeg(double), sinDeg(double), roundDecimals(double x, unsigned short n = 1), ceilDecimals(double x, unsigned short n = 1);
point rotate(point pointToRotate, double angle);
Vector3D rotate(Vector3D, double), rotateTheta(Vector3D, double), rotate(Vector3D, Vector3D);
long long timeIn(double, double);
std::string computeStr(std::string str);

#endif