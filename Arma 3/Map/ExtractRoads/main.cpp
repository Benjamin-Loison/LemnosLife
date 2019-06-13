#include <vector>
#include <string>
#include <iostream>
#include <ctime>
#include <sstream>
#include <windows.h>
#include <sys/time.h>
#include <algorithm>
#include "Scanner.h"
#define RANGE 20
#define PRECISION 0.1
using namespace std;

long long beginTime;

vector<string> listFiles(string directory, string extension, bool withDirectory = false)
{
    WIN32_FIND_DATA FindData;
    HANDLE hFind;
    string fileLookingFor = directory + "*" + extension;
    hFind = FindFirstFile(fileLookingFor.c_str(),&FindData);
    vector<string> files;
    if(hFind == INVALID_HANDLE_VALUE)
        return files;
    do
    {
        string fileName = FindData.cFileName;
        if(withDirectory)
        {
            files.push_back(directory + fileName);
        }
        else
        {
            files.push_back(fileName);
        }
    }
    while(FindNextFile(hFind, &FindData) > 0);
    return files;
}

template<typename T>
string convertNbToStr(const T& number)
{
    ostringstream convert;
    convert << number;
    return convert.str();
}

long long getAbsoluteTime()
{
    struct timeval tp;
    gettimeofday(&tp, NULL);
    return (long long)tp.tv_sec * 1000 + tp.tv_usec / 1000;
}

string getTime()
{
    time_t currentTime = time(0);
    tm* now = localtime(&currentTime);
    return convertNbToStr<int>(now->tm_hour) + ":" + convertNbToStr<int>(now->tm_min) + ":" + convertNbToStr<int>(now->tm_sec);
}

void initializeTimer()
{
    beginTime = getAbsoluteTime();
}

string getEndTimer()
{
    return convertNbToStr<int>(getAbsoluteTime() - beginTime);
}

void print(string toPrint)
{
    cout << getTime() << " " << toPrint << endl;
}

void print(vector<string> arrayToPrint)
{
    string toPrint = "";
    int arrayToPrintSize = arrayToPrint.size();
    for(int index = 0; index < arrayToPrintSize; index++)
    {
        toPrint += arrayToPrint[index];
        if(index != arrayToPrintSize - 1)
        {
            toPrint += '\n';
        }
    }
    print(toPrint);
}

void print(int numberToPrint)
{
    print(convertNbToStr<int>(numberToPrint));
}

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

double convertStrToDouble(string str)
{
    return atof(str.c_str());
}

int main()
{
    print("Begin");

    initializeTimer();

    vector<string> filesPath = listFiles("C:\\Users\\Benjamin\\Desktop\\road\\data\\", "extracted", true);
    int filesPathSize = filesPath.size();
    if(filesPathSize == 0)
    {
        print("No file found !");
    }
    else
    {
        vector<string> roadsData;
        for(int filePathIndex = 0; filePathIndex < filesPathSize; filePathIndex++)
        {
            string filePath = filesPath[filePathIndex];
            print("Working on: " + filePath);
            double roadSegmentX = -1, roadSegmentY = -2, x = -3, y = -4, lineNb = 0;
            string line;
            Scanner scanner = Scanner(filePath);
            do
            {
                line = scanner.nextLine();
                if(contains(line, " [ER] "))
                {
                    vector<string> parts = split(line, " ");
                    string body = "";
                    int partsSize = parts.size();
                    for(int part = 2; part < partsSize; part++)
                    {
                        body += parts[part];
                        if(part != partsSize - 1)
                        {
                            body += " ";
                        }
                    }
                    body = replace(body, "  ", " ");
                    vector<string> bodyParts = split(body, " ");
                    int bodyPartsSize = bodyParts.size();
                    if(bodyPartsSize == 1)
                    {
                        for(unsigned int xRelative = 0; xRelative < body.length(); xRelative++)
                        {
                            char info = body[xRelative];
                            if(info == '@')
                            {
                                x = roadSegmentX - RANGE + xRelative * PRECISION;
                                y = roadSegmentY  - RANGE + lineNb * PRECISION; // PRECISION ?
                                string roadToAdd = convertNbToStr<double>(x) + " " + convertNbToStr<double>(y);
                                if(find(roadsData.begin(), roadsData.end(), roadToAdd) == roadsData.end())
                                {
                                    roadsData.push_back(roadToAdd); // not good coordinates
                                    //print("Add: " + roadToAdd);
                                }
                                else
                                {
                                    print("Do not add duplicated: " + roadToAdd);
                                }
                            }
                        }
                    }
                    else
                    {
                        if(bodyPartsSize == 6)
                        {
                            string roadSegmentXStr = bodyParts[4];
                            roadSegmentX = convertStrToDouble(roadSegmentXStr);
                            string roadSegmentYStr = bodyParts[4];
                            roadSegmentY = convertStrToDouble(roadSegmentYStr);
                            print("Working on road segment: " + roadSegmentXStr + " " + roadSegmentYStr);
                        }
                    }
                }
                lineNb++;
            }
            while(line != "");
        }
    }

    print("Work finished in " + getEndTimer() + " seconds !");
}
