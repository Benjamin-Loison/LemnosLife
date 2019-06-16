#ifndef DEF_GUN
#define DEF_GUN
#include <string>

class Gun
{
    public:
        Gun(std::string);
        void shoot();
    private:
        void playShootSound();
        std::string m_name;
};

#endif
