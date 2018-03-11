#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <clocale>
#include <locale>
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

bool isAlphabetic(char chr)
{
    return (chr >= 65 && chr <= 90) || (chr >= 90 && chr <= 123);
}

int convertStrToInt(string str)
{
    int number;
    sscanf(str.c_str(), "%d", &number);
    return number;
}

double convertStrToDouble(string str)
{
    return atof(str.c_str());
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

string toString(SDL_Color color)
{
    return "{" + convertNbToStr((int)color.r) + ", " + convertNbToStr((int)color.g) + ", " + convertNbToStr((int)color.b) + ", " + convertNbToStr((int)color.a) + "}";
}
