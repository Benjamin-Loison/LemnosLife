#ifndef STRING_PLUS_H_INCLUDED
#define STRING_PLUS_H_INCLUDED
#include <vector>
#include <sstream>
#include <SDL.h>

std::vector<std::string> split(const std::string&, const char *);
std::string replace(std::string, const std::string&, const std::string&), toString(SDL_Color);
int convertStrToInt(std::string);
double convertStrToDouble(std::string);
bool isAlphabetic(char), startsWith(std::string, std::string), contains(std::string, std::string);
long convertStrToLong(std::string);

template<typename T>
std::string convertNbToStr(const T& number)
{
    std::ostringstream convert;
    convert << number;
    return convert.str();
}

#endif
