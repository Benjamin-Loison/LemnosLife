#ifndef DEF_VIEW_GRAVITY
#define DEF_VIEW_GRAVITY

#include "../ViewAngle.h"
#include "View.h"
#include "../../../Physics/GravityPosition.h"
#include "../Position.h"
#include "../../../3D/Render/Engine/vector3d.h"

class ViewGravity
{
public:
    ViewGravity(GravityPosition = GravityPosition(), ViewAngle = ViewAngle());
    ViewGravity(std::vector<std::string>);
    ViewGravity(View);
    void updateViewGravity(ViewGravity), updateViewGravityWithoutGravity(ViewGravity);
    ViewGravity updateGravityPosition(GravityPosition), updateViewAngle(ViewAngle), updateOrientation(Position), updatePosition(Position);//, updatePosition(User*);
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

//#include "User.h"

//ViewGravity updatePosition(ViewGravity*, User*); // woila c'est relou

#endif
