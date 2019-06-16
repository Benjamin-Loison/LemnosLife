#ifndef CLIENT_H_INCLUDED
#define CLIENT_H_INCLUDED

#include <thread>

extern std::thread network, disconnected;
void initializeNetwork(), sendStr(std::string), closeConnection(), freeNetwork(), sendPosition(), sendOrientation();

#endif
