#ifndef DEF_BIOME
#define DEF_BIOME

#define BIOMES_NUMBER 19
#define BIOME_DEFAULT_ASCII_INDEX 54
#include <string>

void loadBiomeChk1k(std::string);
char getBiome(double[2]), getBiome(double, double, std::string);
std::string getBiomeName(char), getBiomeName(double, double), getBiomeName(double, double, std::string);

extern std::string biomesNames[BIOMES_NUMBER]; 

#endif
