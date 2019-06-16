#ifndef MAP_H_INCLUDED 
#define MAP_H_INCLUDED

#include <string> 
#include <vector> 
#include <map> 
#include <vector> 
#include "MapGLObject.h" 
#include "Structure.h" 
#include "Chunk/Chunk.h" 
#include "../../3D/Render/Engine/API3D.h" 

void initializeMap(), loadStructures(), loadMap(std::string), loadCachedMap(std::string), renderMap(), initializeMapRender(), checkChunkChange(double, double), groundAltitudeRefresh(); 
bool getFirstBool(); 
std::vector<MapGlObject> loadFileSky(std::string); 
extern std::string currentMapFolderPath, structuresFolder, biomesFolder; 
extern std::vector<short> linkStrucVec; 
extern std::map<std::string, Chunk> chunksLoaded; 
extern std::vector<Structure> strucIdDbStruc; 
extern std::vector<std::string> strucIdDbStr; 
extern std::vector<bool> strucIdDbBool; 
extern std::tuple<std::map<std::string, bool>, std::map<std::string, double>, std::map<std::string, long>, std::map<std::string, std::string>> mapData;
extern double groundAltitudeValue;

extern std::vector<Line3D> debugLines;
double getGroundAltitude(bool = false), getGroundAltitude(double, double, bool = false);

#endif 