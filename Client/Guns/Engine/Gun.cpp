#include "Gun.h"
#include <string>
#include "../../Sound/sound.h"
#include "../../Logger/logger.h"
#include "../../StringPlus/string_plus.h"
#include "../../LemnosLife/Render/Engine/engine.h"
#include "../../LemnosLife/Render/Gui/Gui/GuiChat.h"
#include "../../Random/Random.h"
#include "../../Network/Main/client.h"
#include "../../Date/date.h"
#include "../../Physics/GravityPosition.h"
#include <SDL.h>
using namespace std;

map<unsigned int, Bullet> bullets;

bool stopPlease = true;

Bullet::Bullet() {}

Bullet::Bullet(unsigned int itemId, View view, unsigned long timestamp) : m_itemId(itemId), m_view(view)
{
    m_timeBorn = timestamp;
}

void addBullet(unsigned int itemId, View view, unsigned int bulletId, unsigned long timestamp)
{
    bullets[bulletId] = Bullet(itemId, view, timestamp);
}

View Bullet::getInitialView()
{
    return m_view;
}

unsigned long Bullet::getTimeBorn()
{
    return m_timeBorn;
}

unsigned int Bullet::getItemId()
{
    return m_itemId;
}

// could use View later on to add a ViewAngle but now let do not care
Position Bullet::getPosition(unsigned long currentTimestamp) /// ! it seems that timestamp are quickly (about one day) desynchronizing of 1 second ... !
{
    Position pos = m_view.getPosition();
    ViewAngle viewAngle = m_view.getViewAngle();
    /// TODO: SHOULD MAKE SOMETHING TO DEFINE PER FIRE WEAPON THE INITIAL SPEED
    double initialSpeed = 710, // m.s^-1 (ak47 here)
           phi = viewAngle.getPhi(), theta = viewAngle.getTheta(),
           t = (currentTimestamp - m_timeBorn) / 1000.0, // need s not ms // without the .0 it uses integer --' ^^
           x = pos.getX() + initialSpeed * cosDeg(phi) * t,
           y = pos.getY() + initialSpeed * sinDeg(phi) * t,
           z = pos.getZ() + initialSpeed * sinDeg(theta) * t - EARTH_GRAVITY * pow(t, 2) / 2; /// for air resistance could consider variable air density depending on altitude, exmaple: https://upload.wikimedia.org/wikipedia/commons/6/6b/Atmosph%C3%A4re_Dichte_600km.png
    return Position(x, y, z);
}

// historical simplest model: if targeting user and shot then just kill him
void renderBullets()
{
    // compute here the time in millis and provide it to compute coordinates or compute time in the function to get coordinates ? let say first option likewise draw a kind of paused scene (+ is it a costly in time function to get time ?)
    return; ///////////////////////////////////////////////////////!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    unsigned long currentTime = getMillis();
    for(map<unsigned int, Bullet>::iterator it = bullets.begin(); it != bullets.end(); it++)
    {
        unsigned int bulletIndex = it->first;
        Bullet* bullet = &it->second;
        unsigned long timeBorn = bullet->getTimeBorn(), timeLived = currentTime - timeBorn;
        View view = bullet->getInitialView();
        Position pos = bullet->getPosition(currentTime);
        //addChatMessage("Bullet: " + convertNbToStr(bulletIndex) + " " + /*view.getPosition().toString()*/pos.toString() + " " + view.getViewAngle().toString() + " " + convertNbToStr(timeLived));
        // could make a clean print(print with a must-have number of digits)
        // don't need orientation in position toString and structure in general only works with phi and theta angles - solved (used to be: view.toString())
        /*if(timeLived > BULLET_TIME_TO_LIVE) // let the server do it ! JUST DO IT // could also make it here to be more precise but let us don't care, server latency could make visible bullets for a few milliseconds (ping / 2) while they should be stopped on the "wall"
        {
            addChatMessage("Removed previous bullet !");
            bullets.erase(bulletIndex);
        }*/
    }
}

Gun::Gun(string name, Selector selector, unsigned short shotTime, double recoil, unsigned int maxStack, unsigned short width, unsigned short height) : Item(name, maxStack, width, height), m_selector(selector), m_shooting(false), m_shotTime(shotTime), m_recoil(recoil)
{
}

Selector Gun::getSelector()
{
    return m_selector;
}

void playShootSound(unsigned short id)
{
    playSound(getItemName(id) + "_fire_0");
}

void Gun::realShoot()
{
    //if ammo
    if(m_selector == SEMI_AUTOMATIC)
        playShootSound();
    else
    {
        do
        {
            playShootSound();
            //print(convertNbToStr(m_shotTime));
            SDL_Delay(m_shotTime);
        } while(stopPlease);
    }
    //else sound no more bullet
}

void Gun::setShooting(bool shooting)
{
    m_shooting = shooting;
}

bool Gun::isShooting()
{
    return m_shooting;
}

//thread sT;

#define RECOIL_TIME 100
// could use weapon specific variable in the future

double integrale(double lastTime, double currentTime) // 1 / x^2, intégrale: -1/x entre 1 et 2 et normalise l'intégrale (pour que l'aire entre ces 2 bornes soit égale à 1) par un facteur 2 donc (car l'aire en question fait 1/2)
{
    return 2 * (1 / lastTime - 1 / currentTime);
}

void Gun::recoil()
{
    unsigned long timeEnd = SDL_GetTicks() + RECOIL_TIME;
    double currentTime = SDL_GetTicks(), lastTime = currentTime;
    initializeRandom();
    double randRecoilTheta = randDouble(0, m_recoil), randRecoilPhi = randDouble(0, m_recoil), sommeTheta = 0, sommePhi = 0; // fps propage int ?
    do
    {
        //print("rdT: " + convertNbToStr(randRecoilTheta));
        //print("currentTime: " + convertNbToStr(currentTime));
        //print("lastTime: " + convertNbToStr(lastTime));
        //print("integrale(lastTime, currentTime): " + convertNbToStr(integrale(lastTime, currentTime)));
        double changeTheta = randRecoilTheta * integrale(lastTime, currentTime), changePhi = randRecoilPhi * integrale(lastTime, currentTime);
        //print("e: " + convertNbToStr(changeTheta));
        sommeTheta += changeTheta;
        camera->addTheta(changeTheta);
        sommePhi += changePhi;
        camera->addPhi(sommePhi);
        lastTime = SDL_GetTicks();
        SDL_Delay(1000 / fps);
        currentTime = SDL_GetTicks();
    } while(currentTime < timeEnd);

    double differenceTheta = randRecoilTheta - sommeTheta, differencePhi = randRecoilPhi - sommePhi; // if fps do not follow prediction
    if(differenceTheta != 0)
        camera->addTheta(differenceTheta);
    if(differencePhi != 0)
        camera->addTheta(differencePhi);
}

/*

exemple AK47

vraies données:

portée: 1500m
vitesse initiale: 710 m.s^-1
cadence de tirs: 600 coups/min (soit 10 coups/s)

3 modèles:

1) prend la vitesse initiale telle qu'elle (alors altitude maximale 28 km, portée 50 km, temps de trajet ~160s) = réalisme à petite échelle bon mais à grande échelle du grand n'importe quoi
2) prend la portée (alors altitude maximale = portée donc = 1500 m, vitesse initiale 120 m.s, temps de trajet 28.5s) = à peu près réaliste à grande échelle mais à petite échelle vitesse de la balle relativement faible
3) gérer avec un meilleur modèle les frottements // TODO: coefficient de frottement avec l'air, exemple parachute -mv² ? Modèle de Drude...

pour l'instant utilise modèle numéro 1

*/

void Gun::shoot() /// TODO: use a coefficient to simulate rubs
{
    stopPlease = true;
    m_shooting = true; // ! not auto
    //print("threaded");
    //realShoot();
    thread sT(&Gun::realShoot, this);
    sT.detach();
}

void Gun::stopShooting()
{
    //print("stop it !");
    m_shooting = false;
    stopPlease = false;
    //sT.~thread();
}

unsigned short Gun::getShotTime()
{
    return m_shotTime;
}

// could make recoil depending on targetting in the shoulder axis
void Gun::playShootSound()
{
    //print("shot !");

    // shooting initial position should depend of the gun ...
    sendStr("Shoot " + toString(camera->_position) + " " + convertNbToStr(camera->_phi) + " " + convertNbToStr(camera->_theta)); // "shoot" or "shoot x y z xTarget yTarget zTarget"

    thread cam(&Gun::recoil, this);
    cam.detach();
    //camera->addTheta(1); // add random left/right and threaded to make movement progressivement and as A3, stays up
    //print(m_name + " shot !");
    playSound(m_name + "_fire_0");
}
