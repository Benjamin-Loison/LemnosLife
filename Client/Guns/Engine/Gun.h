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

/// NAMED Guns.h on server
enum Selector {SEMI_AUTOMATIC, AUTOMATIC};

class Gun : public Item
{
    public:
        Gun(std::string, Selector, unsigned short, double, unsigned int, unsigned short, unsigned short);
        void shoot(), stopShooting(), playShootSound(), setShooting(bool), recoil();
        Selector getSelector();
        bool isShooting();
        unsigned short getShotTime();
    private:
        void realShoot();
        bool m_shooting;
        Selector m_selector;
        double m_recoil;
        unsigned short m_shotTime;
};

class Bullet
{
    public:
        Bullet(); // why as always ?
        Bullet(unsigned int, View, unsigned long);
        View getInitialView();
        unsigned int getItemId();
        unsigned long getTimeBorn();
        Position getPosition(unsigned long);
    private:
        unsigned int m_itemId;
        View m_view;
        unsigned long m_timeBorn;
};

void addBullet(unsigned int itemId, View, unsigned int bulletId, unsigned long timestamp) /* no default value for timestamp yet */, renderBullets(); /// itemId doesn't seem to be correct for the moment (bullet item id)

extern std::map<unsigned int, Bullet> bullets; // or could make a function to use .clear()

#endif
