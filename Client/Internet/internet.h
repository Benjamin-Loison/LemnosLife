#ifndef INTERNET_H_INCLUDED
#define INTERNET_H_INCLUDED

#include <string>

#define DATE_SIZE 12
#define FILE_DOWNINFO_EXTENSION ".downInfo"

std::string getInternet(std::string), uploadFile(std::string url, std::string fieldName, std::string filePath);
void initializeInternet(), downloadFileInternet(std::string, std::string, bool update = false), downloadFileHttp(std::string, std::string, bool update = false);
unsigned long long getLocalFileSize(std::string path);

#endif
