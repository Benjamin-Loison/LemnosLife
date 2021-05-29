#ifndef STRING_PLUS_H_INCLUDED
#define STRING_PLUS_H_INCLUDED

#include <vector>
#include <string>
#include <sstream>
#include <map>
#include "../Collisions/Vector2D.h"
#include "../Collisions/3D.h"
#include "../LemnosLife/Map/User/View.h"
#include "../LemnosLife/Map/Position.h"

std::vector<std::string> split(std::string, std::string = " ")/*split(const std::string&, const char *)*/, slice(std::vector<std::string>, unsigned int = 0, int = -1), getKeysVector(std::map<std::string, std::string>*);
std::string replace(std::string, const std::string&, const std::string& = ""), replaceAll(std::string, const std::string&, const std::string& = ""), toString(bool),
            toString(bool[], unsigned short), toString(std::vector<std::string>, std::string = "\n"), toString(std::vector<unsigned int>), toBinaryString(bool),
            toBinaryString(bool[], unsigned short), convertDoubleToStr(double), toString(std::map<std::string, std::string>), isANumber(std::vector<std::string>),
            setLowercase(std::string), toString(std::pair<double, double>), toString(std::vector<Vector2D>), toString(std::vector<Vector3D>, std::string delimiter = " | "),
            toString(Vector2D)/*, toString(View)*/, toString(Position), join(std::vector<std::string>, unsigned int = 0, int = -1, std::string = " "),
            toString(std::tuple<Position, unsigned int, unsigned int>), toString(std::vector<std::tuple<Position, unsigned int, unsigned int>>),
            toString(std::tuple<View, unsigned int, unsigned int>), toString(std::vector<std::tuple<View, unsigned int, unsigned int>>), withSpaces(std::string),
            withSpaces(unsigned long long), withCents(std::string), withCents(unsigned long long), fill(std::string pattern, unsigned int times),
            toString(std::map<unsigned int, std::tuple<View, unsigned int, unsigned int>>), getNbZero(double nb, unsigned short numberOfDigits = 2, bool atTheEnd = false),
            toString(std::pair<Vector3D, double>), toString(std::vector<std::pair<unsigned short, unsigned short>>), toString(OBB), setUppercase(std::string),
            firstUppercase(std::string), getElementInVectorNotConsideringCase(std::vector<std::string>* vecPtr, std::string element), generateRandomString(const int len = 16),
            replaceIgnoreCase(std::string haystack, std::string needle, std::string replacement = "");
int convertStrToInt(std::string);
double convertStrToDouble(std::string);
bool isADouble(std::string), isAnInteger(std::string), isAnInteger(double), isAlphabetic(char), isAlphabetic(std::string), isUppercase(char), startsWith(std::string, std::string),
     endsWith(const std::string&, const std::string&), contains(std::string, std::string), isABool(std::string), convertStrToBool(std::string), convertCharToBool(char),
     isIn(std::vector<std::string>, std::string), isANumber(std::string), isANaturalNumber(std::string), equalsIgnoreCase(std::string, std::string),
     startsWithIgnoreCase(std::string, std::string), equalsIgnoreCase(std::string, std::string), isInNotConsideringCase(std::vector<std::string>*, std::string),
     isAnIPv4(std::string potentialIP);
//std::tuple<bool*, unsigned short> convertStrToBools(std::string);
long long convertStrToLongLong(std::string);
std::map<std::string, std::string> toString(std::map<std::string, bool>), toString(std::map<std::string, double>), toString(std::map<std::string, long long>)/*, toString(std::vector<Vector2D>)*/;
void removeFromVector(std::vector<std::string>*, std::string);
unsigned int getSeconds(std::string), getIndex(std::vector<std::string> vec, std::string toFind);
std::vector<unsigned int> convertStrToUnsignedIntVector(std::string);
std::vector<double> toDouble(std::vector<std::string>); // not directly used
std::vector<double> toDoubleVector(std::string);
std::vector<unsigned long long> toUnsignedLong(std::vector<std::string>);
std::vector<unsigned long long> toUnsignedLongVector(std::string, std::string delimiter = " ");
char setUppercase(char);

/*#define convertStrToBools(strToConvertToBools) \
    ({ \
        unsigned short size = strToConvertToBools.length(); \
        for(unsigned short i = 0; i < size; i++) \
            arr[i] = convertCharToBool(strToConvertToBools[i]); \
		// 0; \
    })*/

#define convertStrToBools(strToConvertToBools) unsigned short size = strToConvertToBools.length(); for(unsigned short i = 0; i < size; i++) arr[i] = convertCharToBool(strToConvertToBools[i]);

template<typename T>
std::string convertNbToStr(const T& number)
{
    std::ostringstream convert;
    convert << number;
    return convert.str();
}

#endif
