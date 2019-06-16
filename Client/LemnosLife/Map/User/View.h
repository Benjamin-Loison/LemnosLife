#ifndef DEF_VIEW
#define DEF_VIEW

#include "../ViewAngle.h"
#include "../Position.h"
#include <string>

class View
{
    public:
        View(Position pos = Position(), ViewAngle = ViewAngle());
        void updateView(View);
        View updatePosition(Position), updateViewAngle(ViewAngle), updateOrientation(Position);
        Position getPosition(), getOrientation();
        ViewAngle getViewAngle();
        const std::string toString();
        bool equals(View const&) const;
    private:
        Position m_pos, m_orientation;
        ViewAngle m_viewAngle;
};

bool operator!=(View const& a, View const& b);

#endif
