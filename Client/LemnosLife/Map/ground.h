#ifndef DEF_GROUND
#define DEF_GROUND

#define SPEED_HEIGHT_LOAD

#include <vector>
#include <string>

void loadGround(bool = false), initGroundRender(), loadAllGroundsGlObjects(), addChunkHeights(std::string, std::tuple<std::vector<std::vector<float>>, std::vector<std::vector<char>>, std::pair<unsigned int, unsigned int>>), loadAGroundChunk(unsigned int, bool = false), loadBiomeAddPart(std::string),
     renderGround(), updateGround(), addGraphicalGround(bool);
extern bool currentGL;
extern std::map<std::string, std::map<std::string, std::vector<std::vector<double>>>> groundDataAllChunk;

#endif
