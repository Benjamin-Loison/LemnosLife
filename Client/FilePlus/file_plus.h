#ifndef FILE_PLUS_H_INCLUDED
#define FILE_PLUS_H_INCLUDED

#include <vector>
#include <string>

#define Gfu6jAQs 94

bool createDirectory(std::string), directoryExists(std::string), doesFileExist(std::string), writeFile(std::string, std::string, std::string), writeFile(std::string, std::string, std::vector<std::string>), removeFile(std::string);
std::vector<std::string> getFileContent(std::string path, bool live = false, bool readComments = true, bool encrypted = false);
std::vector<std::string> listFiles(std::string, std::string, bool = false);
//extern std::string BASIC_CHARS, BASIC_CHARS_WITHOUT_SPACE_BAR;
// doesn't seem used
std::string getFileName(std::string path), getFileContentString(std::string), getFirstLine(std::string filePath);
void listFiles(std::string, std::vector<std::string>*), removeContentInFolder(std::string folderPath, std::string extension);

#endif

