#ifndef AUTH_H_INCLUDED
#define AUTH_H_INCLUDED

#include <map>
#include <tuple> 
#define HASH_LENGTH 100

extern std::map<std::string, std::tuple<std::string, std::string>> usersAuth;
extern std::map<std::string, std::string> sessionIDs;
bool checkPassword(std::string, std::string, std::string = ""), isPasswordCorrect(std::string);
void initializeAuthentification(), writeUsersAuth();
std::string createKey(std::string password);

#endif
