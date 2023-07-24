#ifndef DEF_HUD_VOCAL
#define DEF_HUD_VOCAL

#include "../Gui/Gui.h"

class HudVocal : public Gui
{
public:
    void renderGui(), resizeGui();
    bool isDynamic();
};

#endif
