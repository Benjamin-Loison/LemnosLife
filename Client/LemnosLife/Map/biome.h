#ifndef DEF_BIOME
#define DEF_BIOME

#define BIOMES_NUMBER 19
#define BIOME_DEFAULT_ASCII_INDEX 54
#define BIOME_EXTENSION ".biomes"
#include <string>

void loadBiomeChk1k(std::string, bool = false), setBiome(double x, double y, std::string chk1kName, char biome); // for setBiome removed std::string chk1kName argument in order to be as near as possible to getBiome also done in GuiMap - reverse !
char getBiome(double[2]), getBiome(double, double, std::string);
std::string getBiomeName(char), getBiomeName(double, double), getBiomeName(double, double, std::string);
unsigned short getBiomeIndex(char), getBiomeIndex(std::string biome);
bool isABiome(char biome);

extern std::string biomesNames[BIOMES_NUMBER];

#endif
