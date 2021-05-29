#ifndef FILE_PLUS_H_INCLUDED
#define FILE_PLUS_H_INCLUDED

#include <vector>
#include <string>

bool createDirectory(std::string), directoryExists(std::string), file_exists(std::string), writeFile(std::string filePath, std::string option, std::string toWrite), writeFile(std::string filePath, std::string option, std::vector<std::string> toWrite);
std::vector<std::string> getFileContent(std::string, bool readComents = true), listFiles(std::string, std::string = "", bool = true/*false*/);
std::string getFileName(std::string), getFileContentStr(std::string), getFirstLine(std::string);
int removeFile(std::string);

#endif
