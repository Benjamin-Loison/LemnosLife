#ifndef DEF_HUD_F3
#define DEF_HUD_F3

#include "../Gui/Gui.h"
#define CENTER_COUNT 6

class HudF3 : public Gui
{
    public:
        void renderGui(), resizeGui();
        bool isDynamic();
    private:
        double m_widthDiv2, m_centerX, m_centerY[CENTER_COUNT], m_lineHeightDiv2;
};

#endif
