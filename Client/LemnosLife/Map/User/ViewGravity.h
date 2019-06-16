#ifndef DEF_VIEW_GRAVITY
#define DEF_VIEW_GRAVITY

#include "../ViewAngle.h"
#include "../../../Physics/GravityPosition.h"
#include "../../../3D/Render/Engine/vector3d.h"
#include "../Position.h"

class ViewGravity
{
    public:
        ViewGravity(GravityPosition = GravityPosition(), ViewAngle = ViewAngle());
        void updateViewGravity(ViewGravity);
        ViewGravity updateGravityPosition(GravityPosition), updateViewAngle(ViewAngle), updateOrientation(Position), updatePosition(Position);
        GravityPosition getGravityPosition();
        GravityPosition* getGravityPositionPtr();
        Position getOrientation();
        ViewAngle getViewAngle();
        Vector3D getVector3D();
        const std::string toString();
    private:
        GravityPosition m_gravityPos;
        Position m_orientation;
        ViewAngle m_viewAngle;
};

#endif
