#ifndef HUD_H_INCLUDED
#define HUD_H_INCLUDED

#include <string>

#include "HudF3.h"
#include "HudHealth.h"
#include "HudChat.h"
#include "HudBroadcast.h"
#include "HudHotbar.h"
#include "HudVehicle.h"
#include "HudNVG.h"
#include "HudCompass.h"
#include "HudWatch.h"
#include "HudGPS.h"
#include "HudBinoculars.h"
#include "HudInteraction.h"
#include "HudVocal.h"
#include "HudWater.h"
#include "HudLoading.h"

#define HUD_NUMBER 15

#define HUD_F3 0
#define HUD_VEHICLE 5
#define HUD_INTERACTION 11
// seems useless (interaction ?)
#define HUD_GPS 9

extern bool hudActivated[HUD_NUMBER];

void initializeHud(),
     addHud(std::string),
     removeHudByIndex(unsigned short hudIndex),
     removeHud(std::string),
     renderHud(),
     switchHud(std::string hud),
     checkHudItems(),
     disableAllHud();
bool switchHudIfHasItem(std::string hud, std::string itemName = "", bool itemWarning = false),
     isHudActivated(std::string hud);
extern HudF3* hudF3Ptr;
extern HudHealth* hudHealthPtr;
extern HudChat* hudChatPtr;
extern HudBroadcast* hudBroadcastPtr;
extern HudHotbar* hudHotbarPtr;
extern HudVehicle* hudVehiclePtr;
extern HudNVG* hudNVGPtr;
extern HudCompass* hudCompassPtr;
extern HudWatch* hudWatchPtr;
extern HudGPS* hudGPSPtr;
extern HudBinoculars* hudBinocularsPtr;
extern HudInteraction* hudInteractionPtr;
extern HudLoading* hudLoadingPtr;
extern std::string picturesHudFolder;

#endif
