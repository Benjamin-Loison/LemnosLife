#ifndef STRING_PLUS_H_INCLUDED
#define STRING_PLUS_H_INCLUDED

//#include "../Vehicles/Vehicle.h"
// doesn't work so let do the toString in Vehicle files
#include <vector>
#include <string>
#include <sstream>
#include <SDL2/SDL.h>
#include <map>
#include <thread>
#include "../3D/Render/Engine/vector3d.h"
#include "../MathPlus/math_plus.h"

#include "../LemnosLife/Map/User/View.h"

//#include "../3D/Render/Engine/API3D.h"

std::vector<std::string> split(std::string, std::string = " ")/*split(const std::string&, const char *)*/, slice(std::vector<std::string>, unsigned int = 0, int = -1), replace(std::vector<std::string>, std::string, std::string), toString(std::vector<std::pair<std::string, Vector3D>>), withCents(std::vector<std::string> vec);
std::string replace(std::string, const std::string&, const std::string& = ""), replaceAll(std::string, const std::string&, const std::string& = ""), toString(SDL_Color), toString(bool), toString(std::vector<std::string>), toString(Vector3D, std::string = " ", unsigned short = UNSIGNED_SHORT_MAX),
    toString(point), toString(line), convertDoubleToStr(double), toBinaryString(bool), generateRandomString(const int = 16), firstUppercase(std::string), withSpaces(long long), withSpaces(std::string), toBinaryStringInt(int),
    toString(std::pair<double, double>)/*, toString(float*, unsigned int)*/, toString(std::tuple</*int, int, unsigned short*/double, double, double>), join(std::vector<std::string>, unsigned int = 0, int = -1, std::string = " "), toString(std::vector<glm::vec3>),
    toStringUnsignedShort(std::tuple<unsigned short, unsigned short>), toString(std::vector<std::tuple<unsigned short, unsigned short>>), toString(std::tuple<View, unsigned int, unsigned int> element), toString(std::map<unsigned int, unsigned int>*),
    setUppercase(std::string), withCents(std::string), withCents(unsigned long long), toString(std::vector<std::vector<double>>), toString(Point), toString(OBB), toString(std::vector<double>)/*, toString(VehicleType)*/,
    toString(std::vector<Vector2D>, std::string delimiter = ";", std::string vector2DDelimiter = " "), toString(std::map<std::string, unsigned int>*), removeAllEmptyCharactersUntilNotEmptyOne(std::string), toString(std::map<std::string, std::string> myMap),
    toString(glm::vec3), toString(glm::vec4), setLowercase(std::string), replaceIgnoreCase(std::string haystack, std::string needle, std::string replacement = ""), toString(std::tuple<std::string, std::string, double> tupl), toString(std::vector<std::tuple<std::string, glm::vec3, glm::vec3>>),
    substring(std::string, unsigned int lowerIndex, unsigned int upperIndex), removeAccents(std::string), getSection(std::string s, std::string delimiter = " ", unsigned int sectionIndex = 0);
int convertStrToInt(std::string);
double convertStrToDouble(std::string);
bool isANumber(std::string), isADouble(std::string), isAnInteger(std::string), isAnInteger(double), isAlphabetic(char), isAlphabetic(std::string), startsWith(std::string, std::string), startsWithIgnoreCase(std::string, std::string), equalsIgnoreCase(std::string, std::string), endsWith(const std::string&, const std::string&),
     contains(std::string, std::string), contains(std::string, char), isABool(std::string), convertStrToBool(std::string), isPasswordCorrect(std::string), isUppercase(char), convertCharToBool(char), isANaturalNumber(std::string), isANaturalNonNullNumber(std::string),
     isOnly(std::string, char), containsWithoutConsideringCase(std::string, std::string), contains(std::vector<std::string>* vec, std::string el), isThreadExecuting(std::thread& th);
long long convertStrToLongLong(std::string);
char setUppercase(char);
std::vector<unsigned int> convertStrToUnsignedIntVector(std::string);
std::vector<double> getDouble(std::vector<std::string>);
unsigned int longestElement(std::vector<std::string>), count(std::string haystack, char chr), getIndex(std::vector<std::string>, std::string); // count not used because was designed to replace split and size but isn't the same things !
std::vector<double> getVec(Vector3D);
void remove(std::vector<std::string>*, std::string), remove(std::vector<std::string>*, unsigned int elIndex), addIfNotIn(std::string el, std::vector<std::string>* vec);

// how does this work ? - clearer after an OpenClassrooms course
template<typename T>
std::string convertNbToStr(const T& number)
{
    std::ostringstream convert;
    convert << number;
    return convert.str();
}

template<typename T>
std::string toString(std::vector<T> vec)
{
    std::string res = "";
    unsigned int vecSize = vec.size();
    for(unsigned int vecIndex = 0; vecIndex < vecSize; vecIndex++)
    {
        unsigned int el = vec[vecIndex];
        res += convertNbToStr(el);
        if(vecIndex < vecSize - 1)
            res += ", ";
    }
    return res;
}

// template for the two following functions ? - yes (double, long long and bool)
template<typename T>
std::map<std::string, std::string> toStringMap(std::map<std::string, T> numberMap)
{
    std::map<std::string, std::string> stringMap;
    for(typename std::map<std::string, T>::const_iterator it = numberMap.begin(); it != numberMap.end(); it++) // the typename is required here don't ask me why
    {
        stringMap[it->first] = convertNbToStr(it->second);
    }
    return stringMap;
}

template<typename T>
std::string toString(std::map<std::string, T> numberMap)
{
    return toString(toStringMap(numberMap));
}

#endif
