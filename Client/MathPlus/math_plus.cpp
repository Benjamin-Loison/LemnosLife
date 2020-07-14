#include "../StringPlus/string_plus.h"
#include "../LemnosLife/Render/Gui/Gui/GuiChat.h"
#include "../Logger/logger.h"
#include "math_plus.h"
using namespace std;

double expression();
unsigned short i = 0;
string s = "";// is there a better system ?

bool isInteger(double k)
{
    return floor(k) == k;
}

double remainderEuclidianDivision(double dividend, double divisor) // TODO: optimize https://en.wikipedia.org/wiki/Division_algorithm#Division_by_repeated_subtraction
{
    /*while(dividend >= divisor)
        dividend -= divisor;
    return dividend;*/
    return fmod(dividend, divisor); // (12)
}

double remainderEuclidianDivisionStrict(double dividend, double divisor)
{
    while(dividend > divisor)
        dividend -= divisor;
    return dividend;
}

long timeIn(double dividend, double divisor)
{
    /// same function at the bottom ?!
    return (dividend - remainderEuclidianDivision(dividend, divisor)) / divisor; /// TODO: see (12) up implement and change with "Méthode binaire" (https://fr.wikipedia.org/wiki/Division_euclidienne) !!!!!!! CHANGE ALL EUCLIDIAN LIKE FUNCTIONS
}

long timeInStrict(double dividend, double divisor)
{
    return (dividend - remainderEuclidianDivisionStrict(dividend, divisor)) / divisor;
}

double distance(double x0, double y0, double x1, double y1)
{
    return sqrt(pow(x1 - x0, 2) + pow(y1 - y0, 2));
}

double distance(double x0, double y0, double z0, double x1, double y1, double z1)
{
    return sqrt(pow(x1 - x0, 2) + pow(y1 - y0, 2) + pow(z1 - z0, 2));
}

double distance(point pt0, point pt1)
{
    return sqrt(pow(pt1.x - pt0.x, 2) + pow(pt1.y - pt0.y, 2));
}

bool isLine(double x0, double x1)
{
    return x0 != x1;
}

/*

y = ax + b
b = y0 - a * x0

*/

line getLine(double x0, double y0, double x1, double y1) // WE ASSUME THAT x0 != x1 (need to test with isLine before) // model: y = ax + b
{
    double a = (y1 - y0) / (x1 - x0);
    return line{a, y0 - a * x0};
}

line getLine(point A, point B) // requires up fonction ?
{
    return getLine(A.x, A.y, B.x, B.y);
}

bool isIntersection(line l0, line l1)
{
    return l0.a != l1.a;
}

/*

unknowns: x, y

y = a0 * x + b0
y = a1 * x + b1

y - a0 * x = b0
y - a1 * x = b1

#Cramer

Delta = a0 - a1

|e c| |a e| that is |b0 -a0| |1 b0|
|f d| |b f|         |b1 -a1| |1 b1|

respectively:

a0 * b1 - a1 * b0
b1 - b0

x = (a0 * b1 - a1 * b0) / Delta
y = (b1 - b0) / Delta

*/

double cramersDeterminant(Vector2D CD, Vector2D CA)
{
    return CD.X * CA.Y - CA.X * CD.Y;
}

pair<double, double> solveSystem2Equations2Unknowns(Vector2D CD, Vector2D CA, Vector2D E) // assume cramers determinant != 0
{
    double det = cramersDeterminant(CD, CA);
    if(det != 0)
    {
        pair<double, double> unknowns;
        unknowns.first = (E.X * CA.Y - CA.X * E.Y) / det;
        unknowns.second = (E.Y * CD.X - CD.Y * E.X) / det;
        return unknowns;
    }
    else
        ;
}

point getIntersection(line l0, line l1) // WE ASSUME THAT a0 != a1 (need to test with isIntersection before)
{
   double delta = l0.a - l1.a;
   return point{(l0.a * l1.b - l1.a * l0.b) / delta, (l1.b - l0.b) / delta};
}

point rotate(point pointInstance, double angle)
{
    double cosed = cos(angle), sined = sin(angle);
    return point{pointInstance.x * cosed - pointInstance.y * sined, pointInstance.x * sined + pointInstance.y * cosed};
    // BULLSHIT DOESN'T CONSIDER angle... return point{-pointInstance.y, pointInstance.x}; // MAY DO NOT APPRECIATE PERMUTATION
}

// middle, left
point rotate(point pointToRotate, point rotationPoint, double angle)
{
    pointToRotate.x -= rotationPoint.x;
    pointToRotate.y -= rotationPoint.y;
    pointToRotate = rotate(pointToRotate, angle);
    pointToRotate.x += rotationPoint.x;
    pointToRotate.y += rotationPoint.y;
    return pointToRotate;
}

point rotateResize(point pointToRotate, point rotationPoint, double angle, double distance)
{
    pointToRotate.x -= rotationPoint.x;
    pointToRotate.y -= rotationPoint.y;
    pointToRotate = resize(rotate(pointToRotate, angle), distance);
    pointToRotate.x += rotationPoint.x;
    pointToRotate.y += rotationPoint.y;
    return pointToRotate;
}

Matrix getRotation3D(double theta, double phi, double roll)
{
    double cosTheta = cosDeg(theta), sinTheta = sinDeg(theta),
    cosPhi = cosDeg(phi), sinPhi = sinDeg(phi),
    cosRoll = cosDeg(roll), sinRoll = sinDeg(roll);

    Matrix rot = Matrix(3, 3);

    rot.set(0, 0, cosRoll * cosPhi - sinRoll * cosTheta * sinPhi);
    rot.set(0, 1, -cosRoll * sinPhi - sinRoll * cosTheta * cosPhi);
    rot.set(0, 2, sinRoll * sinTheta);

    rot.set(1, 0, sinRoll * cosPhi + cosRoll * cosTheta * sinPhi);
    rot.set(1, 1, -sinRoll * sinPhi + cosRoll * cosTheta * cosPhi);
    rot.set(1, 2, -cosRoll * sinTheta);

    rot.set(2, 0, sinTheta * sinPhi);
    rot.set(2, 1, sinTheta * cosPhi);
    rot.set(2, 2, cosTheta);
    //addChatMessage("rot3D matrix: " + rot.toString());

    return rot;
}

Vector3D rotate(Vector3D vec, double angle)
{
    point p = rotate(point{vec.X, vec.Y}, angle);
    return Vector3D(p.x, p.y, vec.Z);
}

Vector3D rotation(Vector3D A, double theta, double phi, double roll) // use ... ?
{
    Matrix rot3D = getRotation3D(theta, phi, roll), AM = Matrix(A), res = (AM.transpose()).product(rot3D);
    addChatMessage("x: rot3D: " + rot3D.toString() + "\nA: " + toString(A) + "\nAM: " + AM.toString() + "\nres: " + res.toString());
    return res.toVec3D();
}

Vector3D rotate(Vector3D pointToRotate, Vector3D rotationPoint, double theta, double phi, double roll)
{
    addChatMessage("rotate: " + toString(pointToRotate) + " " + toString(rotationPoint) + " " + convertNbToStr(theta) + " " + convertNbToStr(phi) + " " + convertNbToStr(roll));
    // to origin
    pointToRotate.X -= rotationPoint.X;
    pointToRotate.Y -= rotationPoint.Y;
    pointToRotate.Z -= rotationPoint.Z;

    // rotating stuff
    pointToRotate = rotation(pointToRotate, theta, phi, roll);
    addChatMessage("pointToRotate: " + toString(pointToRotate));

    // reset origin
    pointToRotate.X += rotationPoint.X;
    pointToRotate.Y += rotationPoint.Y;
    pointToRotate.Z += rotationPoint.Z;

    return pointToRotate;
}

Vector3D rotate(Vector3D pointToRotate, ViewAngle viewAngle)
{
    return rotate(pointToRotate, Vector3D(), viewAngle.getTheta(), viewAngle.getPhi(), viewAngle.getRoll());
}

Vector3D rotate(Position pointToRotate, ViewAngle viewAngle)
{
    return rotate(pointToRotate.getVec(), viewAngle/*Vector3D(), viewAngle.getTheta(), viewAngle.getPhi(), viewAngle.getRoll()*/);
}

point reverse(point pt)
{
    return point{pt.y, pt.x};
}

/*point rotateAbsoluteDistance(point pointInstance, double angle, double distance)
{
    double cosed = cos(angle), sined = sin(angle);
    return point{pointInstance.x * cosed - pointInstance.y * sined, pointInstance.x * sined + pointInstance.y * cosed};
    // BULLSHIT DOESN'T CONSIDER angle... return point{-pointInstance.y, pointInstance.x}; // MAY DO NOT APPRECIATE PERMUTATION
}

point rotateAbsoluteDistance(point pointToRotate, point rotationPoint, double angle, double distance)
{
    pointToRotate.x -= rotationPoint.x;
    pointToRotate.y -= rotationPoint.y;
    pointToRotate = rotate(pointToRotate, angle);
    pointToRotate.x += rotationPoint.x;
    pointToRotate.y += rotationPoint.y;
    return pointToRotate;
}*/

point getMiddle(point p0, point p1)
{
    return point{(p0.x + p1.x) / 2, (p0.y + p1.y) / 2};
}

double min(double x, double y)
{
    return (x < y) ? x : y;
}

double min(double x, double y, double z, double w)
{
    return min(min(min(x, y), z), w);
}

double max(double x, double y)
{
    return (x > y) ? x : y;
}

double max(double x, double y, double z, double w)
{
    return max(max(max(x, y), z), w);
}

long integerDivision(double x, double y)
{
    return (long)((x - remainderEuclidianDivisionStrict(x, y)) / y);
}

long integerIn(double x, double y)
{
    return (long)(x - remainderEuclidianDivisionStrict(x, y));
}

point getPoint(Vector2D vec2d)
{
    return point{vec2d.X, vec2d.Y};
}

Vector2D getVector2D(point pt)
{
    return Vector2D(pt.x, pt.y);
}

double getRadians(double degrees)
{
    return M_PI * degrees / 180;
}

double getDegrees(double radians)
{
    return 180.0 * radians / M_PI;
}

double cosDeg(double deg)
{
    return cos(getRadians(deg)); // no std function ?
}

double sinDeg(double deg)
{
    return sin(getRadians(deg));
}

char peek()
{
    return s[i];
    //return *expressionToParse;
}

char get()
{
    char p = peek();
    i++;
    return p;
    //return *expressionToParse++;
}

double pow(double x, unsigned short n)
{
    if(n == 0) return 1;
    double res = pow(x, n / 2);
    return res * res * ((n % 2 != 0) ? x : 1);
}

double number()
{
    double result = get() - '0', ent = 0;
    unsigned short i = 0;
    bool doted = false;
    while(peek() >= '0' && peek() <= '9' || peek() == '.')
    {
        if(peek() == '.')
        {
            get();
            ent = result;
            result = 0;
            i = 0;
            doted = true;
        }
        else
        {
            result = 10 * result + get() - '0';
            i++;
        }
    }
    return doted ? ent + result / pow(10, i) : result;
}

double factor()
{
    if(peek() >= '0' && peek() <= '9')
        return number();
    else if (peek() == '(')
    {
        get(); // '('
        double result = expression();
        get(); // ')'
        return result;
    }
    else if (peek() == '-')
    {
        get();
        return -factor();
    }
    return 0; // error
}

double term()
{
    double result = factor();
    while(peek() == '*' || peek() == '/')
        result *= (get() == '*') ? factor() : 1 / factor();
    return result;
}

double expression()
{
    double result = term();
    while(peek() == '+' || peek() == '-')
        result += (get() == '+') ? term() : -term();
    return result;
} // revoir le sens de cet algorithme

double compute(string str)
{
    s = str;
    i = 0;
    return expression();
}

Matrix::Matrix() {}

Matrix::Matrix(unsigned short n, unsigned short p) : m_n(n), m_p(p)
{
    vector<double> column;
    for(unsigned short i = 0; i < n; i++)
    {
        column.push_back(0);
    }
    for(unsigned short j = 0; j < p; j++)
    {
        m_data.push_back(column);
    }
}

Matrix::Matrix(Vector3D A) : m_n(3), m_p(1)
{
    //m_data.clear();
    vector<double> column = getVec(A);
    m_data.push_back(column);
    //addChatMessage("M: " + toString() + " v: " + convertNbToStr(column[0]) + " " + convertNbToStr(m_data.size()) + " " + convertNbToStr(m_data[0][0]));
    //addChatMessage("M: " + convertNbToStr(m_n) + " " + convertNbToStr(m_p) + " " + toString(A) + " " + toString(column) + " " + toString(m_data));
}

void Matrix::set(unsigned short i, unsigned short j, double value)
{
    m_data[i][j] = value;
}

double Matrix::get(unsigned short i, unsigned short j)
{
    if(i >= m_n || j >= m_p || m_data.size() < m_n || m_data[0].size() < m_p) // sure last conditions ?
    {
        print("double Matrix::get(unsigned short, unsigned short) has bad arguments !");
        return -42;
    } // this shouldn't happened !
    return m_data[i][j];
}

string Matrix::toString() /// if one of n, p has value 255 for loops while become infinite one
{
    string res = "";
    for(unsigned short i = 0; i < m_n; i++)
    {
        for(unsigned short j = 0; j < m_p; j++)
        {
            res += convertNbToStr(/*get(i, j)*/m_data[j][i]);
            if(j < m_p - 1)
                res += " ";
        }
        if(i < m_n - 1)
            res += "\n";
    }
    return res;
}

Matrix Matrix::product(Matrix B)
{
    Matrix C = Matrix(m_n, B.getP()); // I would like to use native arrays but need to precise first dimension
    if(m_p == B.getN())
    {
        for(unsigned short i = 0; i < C.getN(); i++)
        {
            for(unsigned short j = 0; j < C.getP(); j++)
            {
                for(unsigned short k = 0; k < C.getN(); k++)
                {
                    C.m_data[i][j] += m_data[i][k] * B.m_data[k][j];
                }
            }
        }
    }
    return C;
}

Matrix Matrix::transpose()
{
    Matrix T = Matrix(m_p, m_n); // don't need a temporary matrix :)
    for(unsigned short i = 0; i < m_n; i++)
    {
        for(unsigned short j = 0; j < m_p; j++)
        {
            T.m_data[i][j] = m_data[j][i];
        }
    }
    return T;
}

Vector3D Matrix::toVec3D()
{
    Vector3D vec = Vector3D();
    if(m_n >= 1 && m_p >= 3)
    {
        vec.X = m_data[0][0];
        vec.Y = m_data[1][0];
        vec.Z = m_data[2][0];
    }
    return vec;
}

unsigned short Matrix::getN()
{
    return m_n;
}

unsigned short Matrix::getP()
{
    return m_p;
}
