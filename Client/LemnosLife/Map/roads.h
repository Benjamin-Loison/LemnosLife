#ifndef DEF_ROADS
#define DEF_ROADS

#define ROADS_NUMBER 5

#include "../../2D/vector2d.h"
#include <SDL2/SDL.h>

void initializeRoads(),
     loadRoads(bool = false, std::string middleCurrentChunk = ""),
     initRoadsRender(),
     renderRoads();
bool isOnRoad(double, double),
     isOnRoadInt(int, int),
     isIn(point);
unsigned short getRoad(double, double);
extern SDL_Color roadsColor[ROADS_NUMBER];
point getPointStr(std::string);
// used to be: extern std::vector<std::tuple<int, int, unsigned short>> roadsSubChunkGround;
extern std::vector<std::pair<int, int>> roadsSubChunkGround[ROADS_NUMBER];
extern std::string pathToRoadsDataFileBinFile;

#endif
