#ifndef DEF_HUD_BINOCULARS
#define DEF_HUD_BINOCULARS

#include "../Gui/Gui.h"

class HudBinoculars : public Gui
{
public:
    void renderGui(), resizeGui();
    bool isDynamic();
};

#endif
