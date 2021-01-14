#include <string>
//#include "BCrypt.hpp"
#include "../Network/Main/client.h"
#include "../FilePlus/configuration.h"
#include "../StringPlus/string_plus.h"
#include "../Logger/logger.h"
#include "bcrypt.h"
#define HASH_LENGTH 100
using namespace std;

string hashPassword(string password)
{
    char hash[61];
    string answer = queryServer("Salt " + configurationData["username"]);
    //unsigned short logRound = convertStrToInt(answer.substr(5, 2));
    //string salt = answer.substr(8, 22);
    ///bcrypt_checkpass(password.c_str(), replace(answer, "Salt ").c_str());
    //return BCrypt::generateHash(password.c_str(), salt, logRound);
    return bcrypt_checkpass(password.c_str(), replace(answer, "Salt ").c_str());
}

string createKey(string password)
{
    char hash[HASH_LENGTH];
    bcrypt_newhash(password.c_str(), 8, hash, HASH_LENGTH);
    return string(hash);
}
