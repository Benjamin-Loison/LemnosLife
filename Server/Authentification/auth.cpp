#include "../FilePlus/file_plus.h"
#include "../StringPlus/string_plus.h"
#include "../LemnosLife/Main/main.h"
#include "../Logger/logger.h"
#include "bcrypt.h"
#include "auth.h"
#include <vector>
#include <map>
#include <tuple>
using namespace std;

map<string, tuple<string, string>> usersAuth; // [Prénom Nom] = (ip, hash);
string authFile;
//char *bcrypt_gensalt(uint8_t log_rounds);
//char *bcrypt(const char *pass, const char *salt);
//int bcrypt_checkpass(const char *pass, const char *goodhash); // SURE DOING THE JOB ?
//uint8_t logRound = 8;

void initializeAuthentification()
{
    authFile = authDir + "auth.txt";
    vector<string> lines = getFileContent(authFile);
    for(unsigned linesIndex = 0; linesIndex < lines.size(); linesIndex++)
    {
        string line = lines[linesIndex];
        vector<string> lineParts = split(line);
        if(lineParts.size() != 4)
        {
            print("Line: " + convertNbToStr(linesIndex) + " hasn't three parts: " + line);
            continue;
        }
        usersAuth[lineParts[0] + " " + lineParts[1]] = make_tuple(lineParts[2], lineParts[3]);
        //print(lineParts[0] + " " + lineParts[1] + ": " + lineParts[2] + " " + lineParts[3]);
    }
}

bool checkPasswordIP(string username, string ipv4)
{
    //print("Saved IP: " + get<0>(usersAuth[username]) + " compared with current IP: " + ipv4 + "!");
    return (get<0>(usersAuth[username]) == ipv4)/* && (get<0>(usersAuth[username]) != "")*/;
}

bool checkPassword(string username, string hash, string ipv4) // SURE ?
{
    //print(toString(checkPasswordIP(username, ipv4)) + "@" + toString(passwordRight));
    return hash == "" ? checkPasswordIP(username, ipv4) : !bcrypt_checkpass(hash/*.c_str()*/, (get<1>(usersAuth[username])).c_str());
}

string characters = "~$%&'()*+,-./:;<=>?@[\\]^_`\"{|}~ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";

bool isPasswordCorrect(string password)
{
    unsigned short passwordLen = password.length();
    for(unsigned short passwordIndex = 0; passwordIndex < passwordLen; passwordIndex++)
        if(!contains(characters, password[passwordIndex] + "")) return false;
    return passwordLen >= 8 && passwordLen <= 20;
}

void writeUsersAuth()
{
    vector<string> lines;
    for(map<string, tuple<string, string>>::iterator it = usersAuth.begin(); it != usersAuth.end(); it++)
    {
        lines.push_back(it->first + " " + get<0>(it->second) + " " + get<1>(it->second));
    }
    writeFile(authFile, "w", lines);
}

string createKey(string password)
{
    char hash[HASH_LENGTH];
    bcrypt_newhash(password.c_str(), 8, hash, HASH_LENGTH);
    return string(hash);
}
