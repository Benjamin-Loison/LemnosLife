#ifndef AUTH_H_INCLUDED
#define AUTH_H_INCLUDED

#include <map>
#include <tuple> 

extern std::map<std::string, std::tuple<std::string, std::string>> usersAuth;
bool checkPassword(std::string, std::string, std::string = "");
void initializeAuthentification();

#endif
