#ifndef NETWORK_H_INCLUDED
#define NETWORK_H_INCLUDED

#include "../../LemnosLife/Map/User/User.h"

bool manageNetwork(/*std::vector<std::string>* msgPointer, */std::string message, std::vector<std::string> elements, unsigned int elementsSize, User* user, std::string ip, std::string port, bool forceShop);

#endif
