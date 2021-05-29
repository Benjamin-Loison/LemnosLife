/*#ifndef DEF_GRAVITY_POSITION
#define DEF_GRAVITY_POSITION

// files copied from client

#include "../LemnosLife/Map/Position.h"
#define EARTH_GRAVITY 9.8

#include <vector>
#include <string>

class GravityPosition: public Position
{
    public:
        GravityPosition(double x = 0, double y = 0, double z = 0);
        GravityPosition(std::vector<std::string>);
        void beginFreeFall(bool = false), applyGravity(), jump(bool = false), endFreeFall();
        const bool isFalling(bool = false);
        bool m_wantToFall = false, m_wantToStopFall = true;
        double getZDifferenceSinceLastApplication();
    private:
        double m_initialFreeFallHeight = 0, m_lastZTaken = 0, m_jumpSpeed = 0;
        bool m_isFalling = false, m_wantToJump = false, m_isJumping = false;
        unsigned long long m_timeBeginningFreeFall = 0;
};

#endif
*/