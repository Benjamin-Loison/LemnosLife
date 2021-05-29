#ifndef CONFIGURATION_H_INCLUDED
#define CONFIGURATION_H_INCLUDED

#include <tuple>
#include <vector>
#include <map>

//#define BOOL 0
//#define DOUBLE 1
// why it doesn't work only with LONG and STRING
//#define LONG 2
//#define STRING 3

#define C_BOOL 0
#define C_DOUBLE 1
#define C_LONG 2
#define C_STRING 3
//const unsigned short C_BOOL = 0, C_DOUBLE = 1, C_LONG = 2, C_STRING = 3;

extern std::map<std::string, std::string> configurationData, otpKeys;
extern std::vector<std::string> whitelist;
extern std::map<std::string, std::tuple<std::string, unsigned long long, unsigned int, std::string>> blacklist, muteList;
extern std::map<std::string, bool> configurationDataBool;
extern std::map<std::string, long long> configurationDataLong;
extern std::map<std::string, double> configurationDataDouble;
void initializeConfiguration(), freeConfiguration(), saveConfigurationToFile(), writeWhitelist(), writeBlacklist(), writeMuteList(), writeOTPKeys(), writeConfiguration(std::string path, std::map<std::string, std::string> config);
std::map<std::string, std::string> loadConfigurationString(std::string);
std::tuple<std::map<std::string, bool>, std::map<std::string, double>, std::map<std::string, long long>, std::map<std::string, std::string>> loadConfiguration(std::string);
bool isInBlacklist(std::string), isInMuteList(std::string);

#endif
