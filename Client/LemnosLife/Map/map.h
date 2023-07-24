#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED

#include <string>
#include <vector>
#include <map>
#include <vector>
#include <thread>
#include <mutex>
#include "MapGlObject.h"
#include "Structure.h"
#include "Chunk/Chunk.h"
#include "../../3D/Render/Engine/API3D.h"
#include "GroundGl_object.h"

#define ADM_FOR_MAPPING ADMINISTRATOR_ADM
// when map will be clean should change to DEVELOPER maybe should add a grade Mapper/Architecte ? or a permission like building.perm

void initializeMap(), loadMap(std::string, bool = false), loadCachedMap(std::string), renderMap(), initializeMapRender(), checkChunkChange(/*double, double*/bool force = false);
bool getFirstBool(), isCurrentChunkLoading();
extern std::string currentMapFolderPath, structuresFolder, biomesFolder, roadsFolder, farmsFolder;
extern std::map<std::string, Chunk> chunksLoaded; // works with subchunk of 100m
extern std::tuple<std::map<std::string, bool>, std::map<std::string, double>, std::map<std::string, long long>, std::map<std::string, std::string>> mapData;
extern double groundAltitudeValue;
extern bool isMapLoaded, mapLoading;

extern std::vector<Line3D> debugLines;

extern double defaultSpawnX, defaultSpawnY, defaultSpawnZ;
// maybe could unify all these sections ?

// for sea
extern int mapSize;
extern std::string currentChunk;

// for mapUtils
extern std::map<std::string, std::tuple<std::vector<std::vector<float>>, std::vector<std::vector<char>>, std::pair<unsigned int, unsigned int>>> mapChunkHeights;

// for ground
extern unsigned short threadLaunched;
extern std::vector<std::string> groundToRender;

// for objects
extern std::mutex translationsLock, toInitLock;
extern std::string strucIdDbFileName;

extern GroundGl_object groundLoaded[2];

extern std::vector<std::string> filesLoaded;

#endif
