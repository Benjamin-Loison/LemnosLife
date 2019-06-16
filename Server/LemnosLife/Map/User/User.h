#ifndef DEF_USER
#define DEF_USER
#include <string>
#include "View.h"
#include "../map.h"
#include "../../Main/main.h"
#include "../../../FilePlus/file_plus.h"
#include <map>

extern double defaultX, defaultY, defaultZ;

class User
{
    public:
        User(std::string = "", View = View(Position(defaultX, defaultY, defaultZ), ViewAngle()), std::string = "-1.-1.-1.-1", unsigned short = 0, unsigned short = 0);
        void initializeTexture(), updateView(View), save();
        View getView();
	std::string getIP();
        unsigned short getUserId(), getPort();
    private:
        std::string m_username, m_ip;
        View m_view;
        unsigned short m_userId, m_port;
};

extern std::map<std::string, User> users;
extern std::string username;
void addUser(std::string), addUser(std::string, View), addUser(std::string, View, std::string), addUser(std::string, View, std::string, unsigned short, unsigned short), initializeUsers();
User* getUserByName(std::string);

#endif
