#ifndef DEF_POSITION
#define DEF_POSITION

#include <string>

class Position
{
    public:
        Position(double x = 0, double y = 0, double z = 0);
        void updatePosition(Position), setX(double), setY(double), setZ(double);
        const double getX(), getY(), getZ();
        const float getXf(), getYf(), getZf();
        const std::string toString();
        bool equals(Position const&) const;
    private:
        double m_x, m_y, m_z;
};

bool operator==(Position const& a, Position const& b);

#endif
