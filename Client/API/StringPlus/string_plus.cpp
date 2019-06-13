#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include "../LemnosLife/Map/map.h"
#include "../Logger/logger.h"
#include "../FilePlus/configuration.h"
#include "string_plus.h"
using namespace std;

template<typename Out>
void split(const string &s, const char *delim, Out result)
{
    stringstream ss;
    ss.str(s);
    string item;
    while (getline(ss, item, *delim))
        *(result++) = item;
}

vector<string> split(const string &s, const char *delim)
{
    vector<string> elems;
    split(s, delim, back_inserter(elems));
    return elems;
}

long convertStrToLong(string str)
{
    return atol(str.c_str());
}

bool startsWith(string subject, string test)
{
    return !subject.compare(0, test.size(), test);
}

bool endsWith(string const& value, string const& ending)
{
    if(ending.size() > value.size()) return false;
    return equal(ending.rbegin(), ending.rend(), value.rbegin());
}

bool isADouble(string strToTest)
{
    strToTest = replace(strToTest, ",", ".");
    unsigned short dotsNumber = 0;
    for(unsigned short strToTestIndex = 0; strToTestIndex < strToTest.length(); strToTestIndex++)
    {
        char chr = strToTest[strToTestIndex];
        if(chr == 46)
            dotsNumber++;
        else if((chr < 48 || chr > 57) && chr != 45)
            return false;
    }
    return dotsNumber == 1;
}

bool isAnInteger(string strToTest)
{
    for(unsigned short strToTestIndex = 0; strToTestIndex < strToTest.length(); strToTestIndex++)
    {
        char chr = strToTest[strToTestIndex];
        if(chr < 48 || chr > 57)
            return false;
    }
    return true;
}

bool isAlphabetic(char chr)
{
    return (chr >= 65 && chr <= 90) || (chr >= 90 && chr <= 123);
}

int convertStrToInt(string str) // unit truncation (no crash)
{
    int number;
    sscanf(str.c_str(), "%d", &number);
    return number;
}

double convertStrToDouble(string str) // WARNING: don't use this for a textfield (user could have a value for 'N' input)
{
    str = replace(str, ",", ".");
    if(str == "N")
        return get<DOUBLE>(mapData)["seaBottom"];
    return atof(str.c_str());
}

string replaceAll(string str, const string& from, const string& to)
{
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != string::npos)
    {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
    }
    return str;
}

string replace(string subject, const string& search, const string& replace)
{
    unsigned int s = subject.find(search);
    if(s > subject.length())
        return subject;
    return subject.replace(s, search.length(), replace);
}

bool contains(string subject, string find)
{
    return subject.find(find) != string::npos;
}

bool isABool(string strToTest)
{
    return strToTest == "true" || strToTest == "false";
}

bool convertStrToBool(string strToConvertToBool)
{
    if(strToConvertToBool == "true")
        return true;
    return false;
}

string toString(SDL_Color color)
{
    return "{" + convertNbToStr((int)color.r) + ", " + convertNbToStr((int)color.g) + ", " + convertNbToStr((int)color.b) + ", " + convertNbToStr((int)color.a) + "}";
}

// if function executed, we suppose that the argument is a bool
string toString(bool value)
{
    if(value == true)
        return "true";
    return "false";
}

map<string, string> toString(map<string, bool> boolMap)
{
    map<string, string> stringMap;
    for(map<string, bool>::iterator it = boolMap.begin(); it != boolMap.end(); it++)
    {
        stringMap[it->first] = toString(it->second);
    }
    return stringMap;
}

// TODO: template for the two following functions ?
map<string, string> toString(map<string, double> doubleMap)
{
    map<string, string> stringMap;
    for(map<string, double>::iterator it = doubleMap.begin(); it != doubleMap.end(); it++)
    {
        stringMap[it->first] = convertNbToStr(it->second);
    }
    return stringMap;
}

map<string, string> toString(map<string, long> longMap)
{
    map<string, string> stringMap;
    for(map<string, long>::iterator it = longMap.begin(); it != longMap.end(); it++)
    {
        stringMap[it->first] = convertNbToStr(it->second);
    }
    return stringMap;
}

string toString(vector<string> vecStr)
{
    string toReturn = "";
    int vecStrSize = vecStr.size();
    for(unsigned int vecStrIndex = 0; vecStrIndex < vecStrSize; vecStrIndex++)
    {
        toReturn += vecStr[vecStrIndex];
        if(vecStrIndex != vecStrSize - 1)
            toReturn += "\n";
    }
    return toReturn;
}

string toString(Vector3D vec3d)
{
    return convertNbToStr(vec3d.X) + " " + convertNbToStr(vec3d.Y) + " " + convertNbToStr(vec3d.Z);
}

string toString(point pointInstance)
{
    return convertNbToStr(pointInstance.x) + " " + convertNbToStr(pointInstance.y);
}
