#ifndef DEF_VIEWANGLE
#define DEF_VIEWANGLE
#include <string>

class ViewAngle
{
    public:
        ViewAngle(std::string, std::string = " ");
        ViewAngle(double phi = 0, double theta = 0, double roll = 0);
        void updateViewAngle(ViewAngle);
        const double getPhi(), getTheta(), getRoll();
        const std::string toString(std::string delimiter = " "), toStringWithoutRoll(std::string delimiter = " ");
        bool equals(ViewAngle const&) const, isStriclySmallerThan(ViewAngle const&) const;
    private:
        double m_phi, m_theta, m_roll;
};

bool operator==(ViewAngle const& a, ViewAngle const& b), operator!=(ViewAngle const& a, ViewAngle const& b), operator<(ViewAngle const& a, ViewAngle const& b);

#endif