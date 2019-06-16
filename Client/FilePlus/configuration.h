#ifndef CONFIGURATION_H_INCLUDED
#define CONFIGURATION_H_INCLUDED

#include <SDL.h>
#include <tuple>

#define BOOL 0
#define DOUBLE 1
#define LONG 2
#define STRING 3

extern std::map<std::string, std::string> configurationData;
extern std::map<std::string, bool> configurationDataBool;
extern std::map<std::string, long> configurationDataLong;
extern std::map<std::string, double> configurationDataDouble;
void initializeConfiguration(), freeConfiguration(), saveConfigurationToFile();
std::map<std::string, std::string> loadConfigurationString(std::string);
std::tuple<std::map<std::string, bool>, std::map<std::string, double>, std::map<std::string, long>, std::map<std::string, std::string>> loadConfiguration(std::string);
SDL_Keycode getSDLKey(std::string);

#endif
