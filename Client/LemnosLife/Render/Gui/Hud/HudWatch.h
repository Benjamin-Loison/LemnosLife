#ifndef DEF_HUD_WATCH
#define DEF_HUD_WATCH

#include "../Gui/Gui.h"

class HudWatch : public Gui
{
public:
    void renderGui(), resizeGui();
    bool isDynamic();
};

#endif
