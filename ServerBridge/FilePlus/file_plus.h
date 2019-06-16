#ifndef FILE_PLUS_H_INCLUDED
#define FILE_PLUS_H_INCLUDED

#include <vector>
#include <string>

bool createDirectory(std::string), directoryExists(std::string), file_exists(std::string), writeFile(std::string, std::string, std::string), writeFile(std::string, std::string, std::vector<std::string>);
std::vector<std::string> getFileContent(std::string);
std::vector<std::string> listFiles(std::string, std::string, bool = false);

#endif

