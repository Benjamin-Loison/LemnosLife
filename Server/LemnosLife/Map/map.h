#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED

#include <string>
#include <tuple>
#include <map>
#include <vector>
#include "Chunk/Chunk.h"
//#include <pair> // https://gph.is/2mJRUNC

#define ADM_FOR_MAPPING ADMINISTRATOR_ADM

extern std::string elements, spawnsFilePath, strucIdDbFileName, structuresFolder;
void initializeMap(std::string map), initializeNPCs();
std::string getNPCs(bool withPrefix = true); // take care of user position in order to send good npcs
std::tuple<unsigned int, std::string, double, double, double, double, double, std::string> getNPCById(unsigned int);
extern std::tuple<std::map<std::string, bool>, std::map<std::string, double>, std::map<std::string, long long>, std::map<std::string, std::string>> mapData; // love this variable
extern std::vector<unsigned int> licensePrices;

extern std::map<std::string, std::vector<std::vector<std::vector<double>>>> mapChunkHeights;
extern std::map<std::string, Chunk> chunksLoaded;
extern bool allMapStuffLoaded;

#endif