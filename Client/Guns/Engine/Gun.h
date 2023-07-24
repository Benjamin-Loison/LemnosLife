#ifndef DEF_GUN
#define DEF_GUN

#include "../../LemnosLife/Map/User/Inventory.h"
#include "../../LemnosLife/Map/User/View.h"
#include <string>
#include <thread>

// for debugging
//#define BULLET_TIME_TO_LIVE 300000
#define BULLET_TIME_TO_LIVE 3000
// should be useless even if temporary on server side ? (no in fact it is important to remove computations on the server side)
extern DynamicGl_object bulletImpacts;

/// NAMED Guns.h on server
enum Selector {SEMI_AUTOMATIC, AUTOMATIC};

class Gun : public Item
{
public:
    Gun(std::string, std::string texture, Selector, unsigned short, double, unsigned int, unsigned short, unsigned short, Vector3D rightHand, Vector3D leftHand, double velocity);
    void shoot(), stopShooting(), playShootSound(), setShooting(bool), recoil();
    Selector getSelector();
    bool isShooting();
    unsigned short getShotTime();
    double getVelocity();
private:
    std::string m_name;
    void realShoot();
    bool m_shooting;
    Selector m_selector;
    double m_recoil, m_velocity;
    unsigned short m_shotTime;
    Vector3D m_rightHand, m_leftHand;
};

class Bullet
{
public:
    Bullet(); // why as always ?
    Bullet(unsigned int, View, unsigned long long, double);
    View getInitialView();
    unsigned int getItemId();
    unsigned long long getTimeBorn();
    Position getPosition(unsigned long long);
private:
    unsigned int m_itemId;
    View m_view;
    double m_velocity;
    unsigned long long m_timeBorn;
};

void addBullet(unsigned int itemId, View, unsigned int bulletId, unsigned long long timestamp) /* no default value for timestamp yet */, renderBullets(), initializeGuns(), initializeBulletImpacts(); /// itemId doesn't seem to be correct for the moment (bullet item id)

extern std::map<unsigned int, Bullet> bullets; // or could make a function to use .clear()
// do a shooting range in game ?

#endif
