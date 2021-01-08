#ifndef DEF_POSITION
#define DEF_POSITION

#include <string>
#include <vector>

#include "ViewAngle.h"
#include "../../3D/Render/Engine/vector3d.h"

class Position
{
    public:
        Position(double x = 0, double y = 0, double z = 0);
        Position(std::string, std::string = ",");
        Position(std::vector<std::string>);
        Position(Vector3D);
        void updatePosition(Position), updatePosition(Vector3D), setX(double), setY(double), setZ(double), addX(double), addY(double), addZ(double);
        const double getX() const, getY() const, getZ() const;
        const float getXf() const, getYf() const, getZf() const;
        const std::string toString(std::string delimiter = " ");
        bool equals(Position const&) const, isStriclySmallerThan(Position const&) const;
        std::vector<double> getCoordinates();
        Position &operator += (const Position &v), operator + (const Position &v) const;
        Vector3D getVec();
    private:
        double m_x, m_y, m_z;
};

bool operator==(Position const& a, Position const& b), operator<(Position const& a, Position const& b);

#include <glm.hpp>

glm::vec3 getVec3(Position), getVec3ViewAngle(ViewAngle, bool noOtherRotationThanPhi = false);
/*#include "User/User.h"
#include "../../Vehicles/Vehicle.h"*/
double distance(Position, Position), distance(Position, Vector3D)/*, distance(User*, Vehicle*)*/;

#endif
