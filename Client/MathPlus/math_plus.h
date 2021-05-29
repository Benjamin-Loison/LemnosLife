#ifndef MATH_PLUS_H_INCLUDED
#define MATH_PLUS_H_INCLUDED

#include <cmath>
#include <math.h>
#include "../3D/Render/Engine/vector3d.h"
#include "../LemnosLife/Map/ViewAngle.h"
#include "../LemnosLife/Map/Position.h"
// why here and not in cpp file ?
#include <string>
#include <map>
#include "../2D/vector2d.h"

// The following define isn't required on every plateform
#define M_PI 3.14159265358979323846
#define UNSIGNED_SHORT_MAX 65535
#define UNSIGNED_INT_MAX 4294967295
#define UNSIGNED_LONG_MAX 18446744073709551615
#define CHAR_MAX 127
// is above value correct ?
// need to be long long ?

#include <cereal/archives/binary.hpp>

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
        ///std::vector<std::vector<double>> m_data; // seems to crash if use old matrix data storage method
        double m_data[3][3];
};

point getIntersection(line, line), rotate(point, double = PI_DIVIDED_BY_2), rotate(point, point, double = PI_DIVIDED_BY_2), getMiddle(point, point), rotateResize(point, point, double, double), getPoint(Vector2D), reverse(point);
bool isInteger(double), isLine(double, double), isIntersection(line, line);
line getLine(double, double, double, double), getLine(point, point);
int absolute(int);
double remainderEuclidianDivision(double, double), remainderEuclidianDivisionStrict(double, double), distance(double, double), distance(double, double, double, double), distance(double, double, double, double, double, double), distance(point, point), getMin(double, double),
       getMin(double, double, double, double), getMax(double, double), getMax(double, double, double, double), getRadians(double), cosDeg(double), sinDeg(double), tanDeg(double), compute(std::string str), getDegrees(double radians), epsilon(double),
       roundDecimals(double x, unsigned short n = 1), ceilDecimals(double x, unsigned short n = 1), distance(Vector2D, Vector2D);
long long timeIn(double, double), integerDivision(double, double), integerIn(double, double), timeInStrict(double, double);
Vector2D getVector2D(point), rotate(Vector2D vec, double angle), rotate(Vector2D vec, Vector2D rotationPoint, double angle); // why point and Vector2D both exist ?
std::pair<double, double> solveSystem2Equations2Unknowns(Vector2D, Vector2D, Vector2D);
Vector3D rotate(Vector3D, double), rotate(Vector3D, Vector3D, double theta, double phi, double roll, bool GLSLmethod = false), rotate(Position, ViewAngle), rotate(Position, ViewAngle*), rotate(Vector3D, ViewAngle*);
std::string computeStr(std::string);
unsigned int sum(std::map<std::string, unsigned int>);

// could make a file for cerealizing in my LemnosLife code
/*namespace glm
{
    template<typename Archive> void serialize(Archive& archive, glm::vec4& v4)
    {
        archive(cereal::make_nvp("x", v4.x), cereal::make_nvp("y", v4.y), cereal::make_nvp("z", v4.z), cereal::make_nvp("w", v4.w)); // can do without make_nvp like serializing personnal object in header files
    }

    /*template<typename Archive> void serialize(Archive& archive, glm::vec3& v3)
    {
        archive(cereal::make_nvp("x", v3.x), cereal::make_nvp("y", v3.y), cereal::make_nvp("z", v3.z));
    }*//*

    template<typename Archive> void serialize(Archive& archive, glm::vec2& v2)
    {
        archive(cereal::make_nvp("x", v2.x), cereal::make_nvp("y", v2.y));
    }
}*/

#endif
