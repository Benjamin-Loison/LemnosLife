#ifndef DEF_HUD_NVG
#define DEF_HUD_NVG

#include "../Gui/Gui.h"

class HudNVG : public Gui
{
    public:
        void renderGui(), resizeGui();
        bool isDynamic();
};

#endif
