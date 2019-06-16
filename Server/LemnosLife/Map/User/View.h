#ifndef DEF_VIEW
#define DEF_VIEW

#include "../ViewAngle.h"
#include "../Position.h"
#include <string>

class View
{
    public:
        View(Position = Position(), ViewAngle = ViewAngle());
        void updateView(View);
        View updatePosition(Position), updateViewAngle(ViewAngle);
        Position getPosition();
        ViewAngle getViewAngle();
        const std::string toString();
    private:
        Position m_pos;
        ViewAngle m_viewAngle;
};

#endif
