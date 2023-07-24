#ifndef DEF_VIEWANGLE
#define DEF_VIEWANGLE

#include <string>

class ViewAngle
{
public:
    ViewAngle(double phi = 0, double theta = 0, double roll = 0);
    ViewAngle(std::string, std::string delimiter = " ");
    void updateViewAngle(ViewAngle), setPhi(double), setTheta(double), setRoll(double), addPhi(double), addTheta(double), addRoll(double);
    const double getPhi(), getTheta(), getRoll();
    const std::string toString(std::string delimiter = " ");
    bool equals(ViewAngle const&) const, isStriclySmallerThan(ViewAngle const&) const;
private:
    double m_phi, m_theta, m_roll;
};

bool operator==(ViewAngle const& a, ViewAngle const& b), operator!=(ViewAngle const& a, ViewAngle const& b), operator<(ViewAngle const& a, ViewAngle const& b);

#endif
