#ifndef HUD_H_INCLUDED
#define HUD_H_INCLUDED

#include <string>
#include "HudF3.h"
#include "HudHealth.h"

void initializeHud(), addHud(std::string), removeHud(std::string), renderHud();
extern HudF3 *hudF3Ptr;
extern HudHealth *hudHealthPtr;
extern std::string picturesHudFolder; 

#endif
