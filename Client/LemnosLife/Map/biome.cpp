#include <map>
#include "map.h"
#include "../../FilePlus/file_plus.h"
#include "../../StringPlus/string_plus.h"
#include "../../Logger/logger.h"
#include "../../FilePlus/configuration.h"
#include "../../MathPlus/math_plus.h"
#define BIOME_EXTENSION ".biomes"
#include "biome.h"
using namespace std;

map<string, vector<string>> biomesData;
string biomesNames[BIOMES_NUMBER] = {"dirt", "grassDry", "grassGreen", "concrete", "soil", "beach", "seabed", "thorn", "wildField", "rock", "grassWild", "stony", "forestPine", "mud", "stonyThistle", "marsh", "dead", "desert", "weed"};

void loadBiomeChk1k(string chunkName, bool live) // load biomes of a 1k chunk // TODO: remove from memory when leave chunk...
{
    vector<string> biomesLines = getFileContent(biomesFolder + chunkName + BIOME_EXTENSION, live); // get biome lines of the chunk
    // TODO: create function in string plus.h with string pointer to return a string[] from a vector<string>
    unsigned char biomesLinesSize = biomesLines.size();
    
    for(unsigned char lineIndex = 0; lineIndex < biomesLinesSize; lineIndex++) // line by line
    {
        biomesData[chunkName].push_back(biomesLines[lineIndex]); // assign a line in a var
    }
}

unsigned char indexSub8mChk(double coordinate)
{
    coordinate = (int)remainderEuclidianDivision(coordinate, get<DOUBLE>(mapData)["biomeTileSize"]);
    return coordinate / get<DOUBLE>(mapData)["biomeTileSize"]; // integer quotient (no decimals)
}

unsigned char indexSub8mChk(double coordinate, int chk1kToRemove)
{
    coordinate = (int)coordinate - chk1kToRemove * get<DOUBLE>(mapData)["chunkGroundSize"];
    //if(chk1kToRemove >= 20)
        //print("x0 " + chk1kToRemove);
    return coordinate / get<DOUBLE>(mapData)["biomeTileSize"]; // integer quotient (no decimals)
}

char getBiome(double x, double y)
{
    double coordinates[2] = {x, y};
    string currentChk1k = getChunk1kName(coordinates);
    return biomesData[currentChk1k][indexSub8mChk(y)][indexSub8mChk(x)];
}

char getBiome(double x, double y, string chk1kName)
{
    double coordinates[2] = {x, y};
    if(biomesData.find(chk1kName) == biomesData.end())
    {
        return BIOME_DEFAULT_ASCII_INDEX;
    }
    vector<string> chk1kParts = split(chk1kName, " ");
    return biomesData[chk1kName][indexSub8mChk(y, convertStrToInt(chk1kParts[1]))][indexSub8mChk(x, convertStrToInt(chk1kParts[0]))];
}

string getBiomeName(double x, double y, string chk1kName)
{
    return getBiomeName(getBiome(x, y, chk1kName));
}

string getBiomeName(char biomeId)
{
    unsigned char indexBiomesName = (unsigned char)biomeId;
    if(indexBiomesName >= 48 && indexBiomesName <= 57) //(0-9)
    {
        indexBiomesName -= 48;
    }
    else
    {
        indexBiomesName -= 55; // - 65 (A-H) + 10 (up 10, 0-9))
    }
    return biomesNames[indexBiomesName];
}

string getBiomeName(double x, double y)
{
    return getBiomeName(getBiome(x, y));
}
