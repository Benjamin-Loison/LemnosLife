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

void initializeNetwork(), freeNetwork(), sendAllUsers(std::string, bool = true), sendAllUsersWithoutOne(std::string, std::string, bool = true);
extern std::thread connection;

#endif

