#ifndef DEF_VIEWANGLE
#define DEF_VIEWANGLE
#include <string>

class ViewAngle
{
    public:
        ViewAngle(double phi = 0, double theta = 0);
        void updateViewAngle(ViewAngle);
        const double getPhi(), getTheta();
        const std::string toString();
        bool equals(ViewAngle const&) const;
    private:
        double m_phi, m_theta;
};

bool operator==(ViewAngle const& a, ViewAngle const& b);
bool operator!=(ViewAngle const& a, ViewAngle const& b);

#endif
