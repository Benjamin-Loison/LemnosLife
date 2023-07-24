#ifndef DEF_HUD_GPS
#define DEF_HUD_GPS

#include "../Gui/Gui.h"

class HudGPS : public Gui
{
public:
    void renderGui(), resizeGui();
    bool isDynamic();
};

#endif
