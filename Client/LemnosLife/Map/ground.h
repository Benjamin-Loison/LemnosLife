#ifndef DEF_GROUND
#define DEF_GROUND

#define SPEED_HEIGHT_LOAD

#include <vector>
#include <string>

void loadGround(bool = false, bool encrypted = false), initGroundRender(), loadAllGroundsGlObjects(), addChunkHeights(std::string, std::vector<std::vector<std::pair<std::vector<double>, char>>>), loadAGroundChunk(unsigned int, bool = false, bool encrypted = false), loadBiomeAddPart(std::string),
    renderGround(), updateGround(), addGraphicalGround(bool, bool encrypted = false);
extern bool currentGL;
extern std::map<std::string, std::map<std::string, std::vector<std::vector<double>>>> groundDataAllChunk;

#endif
