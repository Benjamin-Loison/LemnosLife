#ifndef STRING_PLUS_H_INCLUDED
#define STRING_PLUS_H_INCLUDED

#include <vector>
#include <string>
#include <sstream>
#include <map>

std::vector<std::string> split(const std::string&, const char *);
std::string replace(std::string, const std::string&, const std::string&), replaceAll(std::string, const std::string&, const std::string&), toString(bool), toString(std::vector<std::string>);
int convertStrToInt(std::string);
double convertStrToDouble(std::string);
bool isADouble(std::string), isAnInteger(std::string), isAlphabetic(char), startsWith(std::string, std::string), contains(std::string, std::string), isABool(std::string), convertStrToBool(std::string);
long convertStrToLong(std::string);
std::map<std::string, std::string> toString(std::map<std::string, bool>), toString(std::map<std::string, double>), toString(std::map<std::string, long>);

template<typename T>
std::string convertNbToStr(const T& number)
{
	    std::ostringstream convert;
		    convert << number;
			    return convert.str();
}

#endif

