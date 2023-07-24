#ifndef DEF_HUD_COMPASS
#define DEF_HUD_COMPASS

#include "../Gui/Gui.h"

class HudCompass : public Gui
{
public:
    void renderGui(), resizeGui();
    bool isDynamic();
};

// add direciton arrow for item ? (could give the right one)
// do the same for GPS and Watch ?

#endif
