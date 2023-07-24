#ifndef CONFIGURATION_H_INCLUDED
#define CONFIGURATION_H_INCLUDED

#include <SDL2/SDL.h>
#include <tuple>
#include <map>
#include <vector>

#define BOOL 0
#define DOUBLE 1
#define LONG 2
#define STRING 3

extern std::map<std::string, std::string> configurationData;
extern std::map<long long, std::string> keyTranslation;
std::map<long long, std::string> loadConfigurationLong(std::string);
extern std::map<std::string, bool> configurationDataBool;
extern std::map<std::string, long long> configurationDataLong;
extern std::map<std::string, double> configurationDataDouble;
extern bool configurationChanged;
void initializeConfiguration(), freeConfiguration(), saveConfigurationToFile(), saveConfigToFile(std::string configFilePath, std::tuple<std::map<std::string, bool>, std::map<std::string, double>, std::map<std::string, long long>, std::map<std::string, std::string>> data);
std::map<std::string, std::string> loadConfigurationString(std::string);
std::tuple<std::map<std::string, bool>, std::map<std::string, double>, std::map<std::string, long long>, std::map<std::string, std::string>> loadConfiguration(std::string);
SDL_Keycode getSDLKey(std::string);
double getDoubleConfig(std::string key);
bool getBoolConfig(std::string key);
// Why the following line involves compilation issue?
//std::string getStringConfig(std::string key):
extern std::string configurationFolder;
//extern double DEBUG_SIZE;

#endif
