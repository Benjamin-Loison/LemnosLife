#ifndef DEF_VIEW
#define DEF_VIEW

#include "../ViewAngle.h"
#include "../Position.h"
#include <string>

class View
{
    public:
        //View();
        View(std::string);
        View(Position = Position(), ViewAngle = ViewAngle());
        void updateView(View);
        View updatePosition(Position), updateViewAngle(ViewAngle);
        Position getPosition();
        ViewAngle getViewAngle();
        const std::string toString(std::string delimiter = " | ", std::string positionDelimiter = " ", std::string viewAngleDelimiter = " ");
        bool operator !=(View const& a), operator ==(View const& a), isStriclySmallerThan(View const&) const;
    private:
        Position m_pos;
        ViewAngle m_viewAngle;
};

bool operator<(View const& a, View const& b);
View getViewGeographic(double longitude, double latitude);
double distanceView(View view0, View view1);

#endif
