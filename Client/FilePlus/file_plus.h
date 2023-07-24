#ifndef FILE_PLUS_H_INCLUDED
#define FILE_PLUS_H_INCLUDED

#include <vector>
#include <string>

bool createDirectory(std::string), createOneDirectory(std::string), directoryExists(std::string), doesFileExist(std::string), writeFile(std::string, std::string, std::string, bool deleteIfEmpty = false), writeFile(std::string, std::string, std::vector<std::string>, bool deleteIfEmpty = false), removeFile(std::string);
std::vector<std::string> getFileContent(std::string path, bool live = false, bool readComments = true), listFiles(std::string, std::string, bool = false);
//extern std::string BASIC_CHARS, BASIC_CHARS_WITHOUT_SPACE_BAR;
// doesn't seem used
std::string getFileName(std::string path), getFileContentString(std::string), getFirstLine(std::string filePath), getAlternativeServerAssetWithoutBackup(std::string file), getAlternativeServerAsset(std::string file), getAlternativeServerAssetAnyway(std::string file);
void listFiles(std::string, std::vector<std::string>*), removeContentInFolder(std::string folderPath, std::string extension);

#endif

