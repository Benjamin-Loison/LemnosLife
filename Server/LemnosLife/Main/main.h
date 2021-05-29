#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED
#include <string>

extern std::string ext, dir, name, pathSeparatorStr, voiceDir, authDir, mapName/*doesn't used to be extern*/, lemnosLifeDir, mapDir, mapCommonDir, mapPlayedDir, npcsDir, version, farmsDir, warpFile;
extern char pathSeparator;
extern bool DEBUG;
void free(), sigAbrt(int);

#define GAMEMODE_DAYZ
// ...

#endif