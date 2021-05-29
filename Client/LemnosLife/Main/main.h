#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#include <string>
#include <thread>
#include "../../Program/options.h"

#define HAS_INTERNET true

extern std::string name, nameLg, nameUp, version, versionFull, ext, dir, assets, mipMapFile, styles, picturesFolder, downloads, skins, itemsFolder, mapFolder, commonMapFolder, picturesMapFolder, picturesMapGroundFolder, picturesMapRoadsFolder, pathSeparatorStr,
                   animationsStaticFolder, animationsDynamicFolder;
extern char pathSeparator;
extern bool DEBUG;
void free(bool skipEngine = false);

#define THREAD_MAIN 1
#define THREAD_REAL_SHOOT 2
#define THREAD_RECOIL 3
#define THREAD_PARALLEL_CAMERA 4
#define THREAD_INITIALIZE_TEXTURE 5
#define THREAD_LOAD_A_GROUND_CHUNK 6
#define THREAD_CHANGE_CHUNK 7
#define THREAD_RENDER_EVENT 8
#define THREAD_TEXTURE_MANAGER 9
#define THREAD_GAS_STATION_FILL_VEHICLE 10
#define THREAD_SEND_VOCAL 11
#define THREAD_RECORD_VOCAL 12
#define THREAD_PLAY_SOUND 13
#define THREAD_INIT 14
#define THREAD_MANAGE_MSGS 15
#define THREAD_SOUND_MANAGER 16

//#define DEBUG_THREAD_ID
//#define DEBUG_THREAD_ID_END
//extern bool DEBUG_THREAD_ID;

#endif
