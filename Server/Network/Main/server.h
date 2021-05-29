#ifndef SERVER_H_INCLUDED
#define SERVER_H_INCLUDED
#ifdef __linux__
    #include <cstdio>
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <netinet/ip.h>
    #include <unistd.h>
    #define SOCKET int
    #define SOCKADDR_IN struct sockaddr_in
#endif
#ifdef _WIN32
    #include <winsock2.h>
    #include <cstdio>
#endif
#include <thread>
#include <string>
#include <mutex>

#include "../../LemnosLife/Map/User/User.h"

//#define VERSION "1.7.3"
extern std::string VERSION;

#define GAMEPLAY_DAYZ "DayZ"
#define GAMEPLAY_LEMNOS_LIFE "LemnosLife"

#define NETWORK_SEPARATOR "#REP#"

extern std::string NETWORK_SEPARATOR_STR;

extern std::map<std::string, unsigned int> usersLastIncome;

extern std::mutex dontDeleteWorkingUsers;

void initializeNetwork(), freeNetwork(), sendAllUsers(std::string, bool = true), sendAllUsersWithoutOne(std::string, std::string, bool = true, bool notSendToVehicle = false), sendAllBridges(std::string, bool, std::string, std::string),
     sendAllBridges(std::string, bool, std::string, unsigned short), sendAllBridges(std::string, bool, User*)/*not used outside for the moment, now used 8), a nope finally ^^*/, saveServer(), closeServer(), manageMsg(/*std::vector<std::string>*,*/ SOCKET, bool = false),
     sendAllBridgesServChat(std::string, bool, std::string = "", std::string = ""), sendAllBridgesServChat(std::string, bool, std::string = "", unsigned short = 0/*what are these default argument used for ?*/), sendAllBridgesServChat(std::string, bool, User*), disconnect(User*),
     broadcast(std::string color, std::string title, std::string message, std::string username/*, User* destinationUser*/, std::string grade), sendAllBridgesOneByOne(std::string, bool, std::string, std::string),
     sendAllUsersWithoutOne(std::string msg, User* user, bool toArchive = true), saveFilters(), sendAllUsersServChat(std::string, bool toArchive = true);

bool isVersionAllowed(std::string);
std::string block(std::string, std::string);
extern std::thread connection;

extern std::vector<std::string> filters;
extern unsigned int filtersSize;

#endif
