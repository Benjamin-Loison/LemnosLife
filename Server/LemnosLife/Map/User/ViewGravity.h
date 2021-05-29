/*#ifndef DEF_VIEW_GRAVITY
#define DEF_VIEW_GRAVITY

// files copied from client

#include "../ViewAngle.h"
#include "../../../Physics/GravityPosition.h"
#include "../Position.h"
#include "../../../Collisions/Vector3D.h"

class ViewGravity
{
    public:
        ViewGravity(GravityPosition = GravityPosition(), ViewAngle = ViewAngle());
        ViewGravity(std::vector<std::string>);
        void updateViewGravity(ViewGravity), updateViewGravityWithoutGravity(ViewGravity);
        ViewGravity updateGravityPosition(GravityPosition), updateViewAngle(ViewAngle), updateOrientation(Position), updatePosition(Position);
        GravityPosition getGravityPosition();
        GravityPosition* getGravityPositionPtr();
        Position getOrientation();
        ViewAngle getViewAngle();
        ViewAngle* getViewAnglePtr();
        Vector3D getVector3D();
        const std::string toString();
    private:
        GravityPosition m_gravityPos;
        Position m_orientation;
        ViewAngle m_viewAngle;
};

#endif*/