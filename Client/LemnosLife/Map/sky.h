#ifndef DEF_SKY
#define DEF_SKY

#include <vector>
#include <string>
#include "MapGlObject.h"

void loadSky(), renderSky(), initSkyRender();
std::vector<MapGlObject> loadFileSky(std::string);

#endif
