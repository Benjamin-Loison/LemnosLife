#ifndef DEF_HUD_VEHICLE
#define DEF_HUD_VEHICLE

#include "../Gui/Gui.h"

class HudVehicle: public Gui
{
    public:
        void renderGui(), resizeGui();
        bool isDynamic();
};

#endif
