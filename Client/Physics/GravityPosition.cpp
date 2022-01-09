#include "GravityPosition.h"
#include "../Logger/logger.h"
#include "../StringPlus/string_plus.h"
#include "../LemnosLife/Render/Gui/Gui/GuiChat.h"
#include "../LemnosLife/Map/User/User.h"
#include "../FilePlus/configuration.h"
#include "../Network/Main/client.h"
#include "../LemnosLife/Map/mapUtils.h"
#include <SDL2/SDL.h>
#include <math.h>
using namespace std;

GravityPosition::GravityPosition(double x, double y, double z) : Position(x, y, z) {}

GravityPosition::GravityPosition(Position pos) : Position(pos.getX(), pos.getY(), pos.getZ()) {}

GravityPosition::GravityPosition(vector<string> coordinates) : Position(coordinates) {}

void GravityPosition::beginFreeFall(bool wantToJump)
{
    //addChatMessage("0");
    if(isFalling(wantToJump)/* || (getZ() <= getGroundAltitude(getX(), getY()) + 0.1) && wantToJump*/) return;
    //addChatMessage("1");
    if(wantToJump) m_isJumping = true;
    //addChatMessage("2");
    m_isFalling = true;
    m_timeBeginningFreeFall = SDL_GetTicks();
    m_initialFreeFallHeight = getZ();
    m_lastZTaken = m_initialFreeFallHeight;
}

#define ALTITUDE_DEBUG_CONSTANT 1
// could be up to player height ?

// for collisions (vertical and horizontal) there are two models:
// 1. can't connect to obstacles too near (compute hypothenuse etc (greatest distance for the user vertically or horizontally))
// TO PREFER (because can connect to as near as real): 2. cancel move when entering in the obstacle
//
// note1: 1 also need to cancel move after simpler checks
// note2: think about zNear (useful for head rotation)

#define eps 0.0001
// should use a common value for eps (or depending on use) ?

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
        //addChatMessage("4");
        m_wantToFall = false;
        beginFreeFall();
    }
    if(m_wantToJump)
    {
        //addChatMessage("5");
        //if(isFalling(true)) return;
        m_wantToJump = false;
        if(!m_isJumping && !isFalling())
        {
            m_jumpSpeed = 2.8;
            beginFreeFall(true);
        }
    }
    else if(isFalling())
    {
        //addChatMessage("6"); // used to be prints
        Uint32 timeSinceBeginningFreeFall = SDL_GetTicks() - m_timeBeginningFreeFall;
        GravityPosition* gravityPositionPtr = thePlayer->getViewGravity()->getGravityPositionPtr(); // use to be * to get value and not pointer
        double s = timeSinceBeginningFreeFall / 1000.0, z = m_initialFreeFallHeight - (EARTH_GRAVITY * pow(s, 2)) / 2 + m_jumpSpeed * s;

        //addChatMessage(convertNbToStr(SDL_GetTicks()) + " " + convertNbToStr(m_initialFreeFallHeight) + " " + convertNbToStr(m_timeBeginningFreeFall) + " " + convertNbToStr(timeSinceBeginningFreeFall) + " " + convertNbToStr(EARTH_GRAVITY * pow(timeSinceBeginningFreeFall / 1000.0, 2)) + " " + convertNbToStr(((EARTH_GRAVITY * pow(timeSinceBeginningFreeFall / 1000.0, 2)) / 2)));

        // can't use directly m_x etc because declared as private
        double groundAlt = getGroundAltitudeWithStructure(getX(), getY(), getZ() + ALTITUDE_DEBUG_CONSTANT); /// used to use getGroundAltitude(getX(), getY()) everywhere instead of withStructure
        if(z < groundAlt)
        {
            setZ(groundAlt);
            endFreeFall();
            //addChatMessage("1042");
        }

        // mostly copied from freeflycamera.cpp
        double altBottom = getGroundAltitudeWithStructure(getX(), getY(), getZ() + 0.1), altUp = getGroundAltitudeWithStructure(getX(), getY(), getZ() + thePlayer->m_eyeHeight + 0.35); // isn't there any variable which contains user height ?

        //addChatMessage(convertNbToStr(altUp) + " " + convertNbToStr(altBottom) + " " + convertNbToStr(altUp - altBottom)); // why 10^-8 for difference ?
        if(m_isJumping && z > getZ() && altUp > altBottom + eps)
        {
            //z = getZ();
            /*m_jumpSpeed = 0;
            m_isJumping = false;*/
            //addChatMessage("STOP JUMPING LITTLE BUNNY !");
            endFreeFall();
            beginFreeFall();
        }
        else
        {
            //addChatMessage(convertNbToStr(z));
            /*gravityPositionPtr->*/setZ(z);
            ViewGravity viewGravity = ViewGravity(GravityPosition(gravityPositionPtr->getX(), gravityPositionPtr->getY(), z), thePlayer->getViewGravity()->getViewAngle());
            thePlayer->updateViewGravity(viewGravity, true, true); // if doesn't execute this the camera doesn't move
            //sendStr("DEBUG ME");
            sendPosition("gravityPosition");
        }
    }
    else
    {
        //addChatMessage("hello !");
    }
}

// could make a cooldown to jump likewise would be more clean when pressing the space bar for a long long period of time (and simulate kind of stamina by the way)

void GravityPosition::jump(bool wantToJump)
{
    //addChatMessage("7");
    m_wantToJump = true;
    /*addChatMessage("0");
    if(isFalling(true)) return;
    addChatMessage("1");
    m_jumpSpeed = 2.8;
    beginFreeFall(wantToJump);*/
}

double GravityPosition::getZDifferenceSinceLastApplication() /// max jump height is 40 cm
{
    double zDifference = m_lastZTaken - getZ(); // return
    m_lastZTaken = getZ();
    return m_initialFreeFallHeight - getZ();
}

// bug if jump and jump again when back on earth, will jump again - patched and patched also jump when isFalling (without first jump)

// vertical collisions don't work for top of green hut and orange small house and hangar
// TODO: patch pb garage et pont (#ascenseur - when under can jump to the top)
const bool GravityPosition::isFalling(bool wantToJump) // const signifie quoi précisément ?
{
    //addChatMessage("8");
    if(wantToJump) return false;
    //addChatMessage("9");
    double groundAlt = getGroundAltitudeWithStructure(getX(), getY(), getZ() + ALTITUDE_DEBUG_CONSTANT);
    //addChatMessage(convertNbToStr(getZ()) + " " + convertNbToStr(groundAlt));
    /*if(getZ() < groundAlt)
    {
        setZ(groundAlt);
        endFreeFall();
        addChatMessage("10");
    }*/ /// used to be here
    if(!m_isFalling)
    {
        if(getZ() > groundAlt)
        {
            m_wantToFall = true;
            //m_isFalling = true; // to forbid infinite recursive call
            //beginFreeFall();
        }
    }
    //if(getZ() <= getGroundAltitude(getX(), getY()) + 0.1)
      //  m_isFalling = false;
    return m_isFalling;
}

void GravityPosition::endFreeFall()
{
    //double groundAlt = getGroundAltitudeWithStructure(getX(), getY(), getZ() + ALTITUDE_DEBUG_CONSTANT); // if there isn't the constant added, there is a bug when the gravityPositionZ is equal to the surface Z
    //addChatMessage("11");
    //if(getZ() <= groundAlt + 0.1 && getZ() >= groundAlt && m_isJumping) return;
    //addChatMessage("12");
    m_isFalling = false;
    m_isJumping = false;
    m_jumpSpeed = 0;

    // should make a parameter to know whether or not it is the player gravityPosition ? or use a bool return in GuiGame if calls endFreeFall ?
    // https://www.suva.ch/fr-CH/materiel/fiche-thematique/chute-donnees-et-faits-relatifs-au-danger-le-plus-mortel-dans-le-travail-quotidien
    // let say that 8 meters kill and let use a linear model with an offset
    double distanceFallen = m_initialFreeFallHeight - getZ(); /// TODO: should do this on server side ! security issue
    if(!thePlayer->isRidingVehicle() && distanceFallen > 2) /// TODO: 8 meters to die seems underestimate should get a greater number according to killing speed which is 70 km/h
    {
        double toRemove = ((distanceFallen - 2) / 6) * MAX_HEALTH;
        if(toRemove >= 1)
        {
            //addChatMessage("need to remove: " + convertNbToStr(toRemove));
            /// do this on server side (maybe a bug with cars ?)
            /*thePlayer->addHealth(-toRemove);
            addChatMessage("Fallen for: " + convertNbToStr(toRemove));
            sendStr("Health " + convertNbToStr(thePlayer->getHealth()));*/ // no problem precisely here because the user can't add himself health (see checks on server side)
        }
    }
}
