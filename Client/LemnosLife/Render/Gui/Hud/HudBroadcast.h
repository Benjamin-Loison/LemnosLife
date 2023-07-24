#ifndef DEF_HUD_BROADCAST
#define DEF_HUD_BROADCAST

#include "../Gui/Gui.h"

class HudBroadcast : public Gui
{
public:
    void renderGui(), resizeGui(), add(std::string, std::string, std::string, std::string, SDL_Color);
    bool isDynamic();
    std::string title, from, to, message;
    double middleX, middleY, displayTime = 15000, fadeTime = 5000, addedTime, bottom, left, right, top, textY[4];
    SDL_Color titleColor;
};

#endif
