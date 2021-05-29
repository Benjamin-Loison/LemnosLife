#ifndef DEF_BIOME
#define DEF_BIOME

#include <string>
#include "Position.h"

#define BIOMES_NUMBER 19
#define BIOME_DEFAULT_ASCII_INDEX 54
#define BIOME_EXTENSION ".biomes"

char getBiome(Position);
extern std::string biomesNames[BIOMES_NUMBER];
void loadBiomeChk1k(std::string), initializeBiomes();

#endif