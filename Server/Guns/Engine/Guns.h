#ifndef DEF_GUN
#define DEF_GUN

#include "../../LemnosLife/Map/User/Inventory.h"
#include "../../LemnosLife/Map/User/View.h"
#include "../../LemnosLife/Map/User/User.h"

#include <string>

#define BULLET_TIME_TO_LIVE 3000
// temporary macro

enum Selector {SEMI_AUTOMATIC, AUTOMATIC};

class Gun : public Item
{
    public:
        Gun(std::string, Selector, unsigned short, double, unsigned int, unsigned short, unsigned short, Vector3D, Vector3D, double);
        void shoot(), stopShooting(), playShootSound(), setShooting(bool), recoil();
        Selector getSelector();
        bool isShooting();
        double getVelocity();
        unsigned short getShotTime();
    private:
        void realShoot();
        bool m_shooting;
        Selector m_selector;
        double m_recoil, m_velocity; // could make depend velocity on gun and bullet but it doesn't seem that there is a lot of information on the internet about this
        unsigned short m_shotTime;
};

// don't work with Bullet as an item here because we work on the mathematical part and the Bullet as an item need item render so other code is separated (here in fact)

// should make a kind of "paused" mode when the bullet doesn't chronologically move
class Bullet
{
    public:
        Bullet(); // why as always
        Bullet(unsigned int, View, unsigned int, std::string, double);
        unsigned int getBulletIndex(), getItemId();
        unsigned long long getTimeBorn();
        Position getPosition(unsigned long long);
        void checkCollisionsUsers(), checkCollisionsUser(User*);
        bool isTooOld(), checkCollisionsGround(), checkCollisionsStructures();
    private:
        unsigned int m_itemId, m_bulletIndex; 
        View m_view; // m_view is the initial View
        Position m_lastPosition, m_position;
        unsigned long long m_timeBorn;
        bool m_didWaterSound, m_sentToDebugUser;
        double m_velocity;
        std::string m_shooter;
        std::vector<std::string> m_shootedUsernames;
};

Bullet* addBullet(unsigned int itemId, View, std::string);
extern unsigned int lastBulletIndex;
extern std::map<unsigned int, Bullet> bullets;
void initializeGuns(), saveBulletImpacts(), clearBulletImpacts(), loadUserDontRequireAmmo(), saveUserDontRequireAmmo(), removeBullets();
extern std::string bulletImpactsFilePath, debugGunUsername;
bool doesUserDontRequireAmmo(std::string), setUserRequiringAmmo(std::string, bool); // first function isn't anymore used as extern because the old void is now a bool - well first is needed finally

#endif
