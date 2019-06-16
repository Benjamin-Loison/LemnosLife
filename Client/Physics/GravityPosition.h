#ifndef DEF_GRAVITY_POSITION
#define DEF_GRAVITY_POSITION

#include <SDL.h>
#include "../LemnosLife/Map/Position.h"
 
class GravityPosition: public Position
{
    public:
        GravityPosition(double x = 0, double y = 0, double z = 0);
        void beginFreeFall(), applyGravity(), endFreeFall();
        const bool isFalling();
        double getZDifferenceSinceLastApplication();
    private:
        double m_initialFreeFallHeight = 0, m_lastZTaken = 0;
        bool m_isFalling = false;
        Uint32 m_timeBeginningFreeFall = 0;
};
 
#endif