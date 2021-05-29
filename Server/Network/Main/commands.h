#ifndef COMMANDS_H_INCLUDED
#define COMMANDS_H_INCLUDED

#include "../../LemnosLife/Map/User/User.h"

bool manageCommand(std::string message, User* user, std::string ip, std::string port, bool forceShop);

#endif
