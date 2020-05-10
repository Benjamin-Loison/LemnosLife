#include "GravityPosition.h"
#include "../Logger/logger.h"
#include "../StringPlus/string_plus.h"
#include "../LemnosLife/Render/Gui/Gui/GuiChat.h"
#include "../LemnosLife/Map/User/User.h"
#include "../FilePlus/configuration.h"
#include "../Network/Main/client.h"
#include "../LemnosLife/Map/mapUtils.h"
#include <SDL.h>
#include <math.h>
using namespace std;

GravityPosition::GravityPosition(double x, double y, double z) : Position(x, y, z) {}

GravityPosition::GravityPosition(vector<string> coordinates) : Position(coordinates) {}

void GravityPosition::beginFreeFall(bool wantToJump)
{
    print("0");
    if(isFalling(wantToJump)/* || (getZ() <= getGroundAltitude(getX(), getY()) + 0.1) && wantToJump*/) return;
    print("1");
    if(wantToJump) m_isJumping = true;
    print("2");
    m_isFalling = true;
    m_timeBeginningFreeFall = SDL_GetTicks();
    m_initialFreeFallHeight = getZ();
    m_lastZTaken = m_initialFreeFallHeight;
}

void GravityPosition::applyGravity()
{
    /*if(m_wantToStopFall)
    {
        m_wantToStopFall = false;
        setZ(getGroundAltitude(getX(), getY()));
        endFreeFall();
    }*/
    if(m_wantToFall)
    {
        print("4");
        m_wantToFall = false;
        beginFreeFall();
    }
    if(m_wantToJump && !m_isJumping)
    {
        print("5");
        //if(isFalling(true)) return;
        m_wantToJump = false;
        m_jumpSpeed = 2.8;
        beginFreeFall(true);
    }
    else if(isFalling())
    {
        print("6");
        Uint32 timeSinceBeginningFreeFall = SDL_GetTicks() - m_timeBeginningFreeFall;
        GravityPosition gravityPosition = *thePlayer->getViewGravity()->getGravityPositionPtr();
        double s = timeSinceBeginningFreeFall / 1000.0, z = m_initialFreeFallHeight - (EARTH_GRAVITY * pow(s, 2)) / 2 + m_jumpSpeed * s;

        //print(convertNbToStr(SDL_GetTicks()) + " " + convertNbToStr(m_initialFreeFallHeight) + " " + convertNbToStr(m_timeBeginningFreeFall) + " " + convertNbToStr(timeSinceBeginningFreeFall) + " " + convertNbToStr(EARTH_GRAVITY * pow(timeSinceBeginningFreeFall / 1000.0, 2)) + " " + convertNbToStr(((EARTH_GRAVITY * pow(timeSinceBeginningFreeFall / 1000.0, 2)) / 2)));
        ViewGravity viewGravity = ViewGravity(GravityPosition(gravityPosition.getX(), gravityPosition.getY(), z), thePlayer->getViewGravity()->getViewAngle());
        thePlayer->updateViewGravity(viewGravity, true, true);
        sendPosition();
    }
}

void GravityPosition::jump(bool wantToJump)
{
    print("7");
    m_wantToJump = true;
    /*print("0");
    if(isFalling(true)) return;
    print("1");
    m_jumpSpeed = 2.8;
    beginFreeFall(wantToJump);*/
}

double GravityPosition::getZDifferenceSinceLastApplication()
{
    double zDifference = m_lastZTaken - getZ(); // return
    m_lastZTaken = getZ();
    return m_initialFreeFallHeight - getZ();
}

const bool GravityPosition::isFalling(bool wantToJump)
{
    //print("8");
    if(wantToJump) return false;
    //print("9");
    double groundAlt = getGroundAltitude(getX(), getY());
    if(getZ() < groundAlt)
    {
        setZ(groundAlt);
        endFreeFall();
        print("10");
    }
    //if(getZ() <= getGroundAltitude(getX(), getY()) + 0.1)
      //  m_isFalling = false;
    return m_isFalling;
}

void GravityPosition::endFreeFall()
{
    double groundAlt = getGroundAltitude(getX(), getY());
    //print("11");
    //if(getZ() <= groundAlt + 0.1 && getZ() >= groundAlt && m_isJumping) return;
    print("12");
    m_isFalling = false;
    m_isJumping = false;
    m_jumpSpeed = 0;
}
