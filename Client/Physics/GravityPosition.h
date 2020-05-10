#ifndef DEF_GRAVITY_POSITION
#define DEF_GRAVITY_POSITION

#include <SDL.h>
#include "../LemnosLife/Map/Position.h"
#define EARTH_GRAVITY 9.8

//const double EARTH_GRAVITY = 9.8/*0665*/;

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
        Uint32 m_timeBeginningFreeFall = 0;
};

#endif
