#ifndef DEF_HUD_WATER
#define DEF_HUD_WATER

#include "../Gui/Gui.h"

class HudWater : public Gui
{
    public:
        void renderGui(), resizeGui();
        bool isDynamic();
};

#endif
