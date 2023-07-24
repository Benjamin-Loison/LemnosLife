#ifndef DEF_VIEW
#define DEF_VIEW

#include "../ViewAngle.h"
#include "../Position.h"
#include <string>

class View
{
public:
    View(std::string);
    View(Position pos = Position(), ViewAngle = ViewAngle());
    void updateView(View);
    View updatePosition(Position), updateViewAngle(ViewAngle), updateOrientation(Position);
    const Position getPosition(), getOrientation();
    ViewAngle getViewAngle();
    const std::string toString(std::string delimiter = " | ");
    bool equals(View const&) const, isStriclySmallerThan(View const&) const; // to remove (to keep ==) ? #NeedConventions, no keep both because this one can be used with pointers, not == ?
private:
    Position m_pos, m_orientation;
    ViewAngle m_viewAngle;
};

bool operator!=(View const& a, View const& b), operator==(View const& a, View const& b), operator<(View const& a, View const& b);

#endif
