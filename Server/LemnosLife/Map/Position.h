#ifndef DEF_POSITION
#define DEF_POSITION

#include <string>
// otherwise there is a problem
//#include "../../MathPlus/math_plus.h"

class Position
{
    public:
        Position(double x = 0, double y = 0, double z = 0);
        Position(std::string, std::string = ",");
        void updatePosition(Position), addZ(double);
        const double getX(), getY(), getZ();
        const std::string toString(std::string delimiter = " ", unsigned short precision = /*UNSIGNED_SHORT_MAX*/65535), toString2D(std::string delimiter = " "), toString2DGeographic(); // second delimiter isn't used with another value than the default one
        bool equals(Position const&) const, isStriclySmallerThan(Position const&) const;
        //Position &operator += (const Position &v), operator + (const Position &v) const;
    private:
        double m_x, m_y, m_z;
};

bool operator==(Position const& a, Position const& b), operator!=(Position const& a, Position const& b), operator<(Position const& a, Position const& b);
double distance(Position pos0, Position pos1);

#endif
