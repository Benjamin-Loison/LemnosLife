#ifndef DEF_HUD_HEALTH
#define DEF_HUD_HEALTH

#include "../Gui/Gui.h"
#define ICON_NUMBER 5
#define ICON_OFFSET 2

class HudHealth : public Gui
{
    public:
        void renderGui(), resizeGui();
        bool isDynamic();
    private:
        double m_centerX, m_centerY[ICON_NUMBER], m_widthDiv2, m_lineHeightDiv2, m_bottomLeftIconX, m_bottomLeftIconY[ICON_NUMBER], m_topRightIconX, m_topRightIconY[ICON_NUMBER];
};

extern bool displayHealth;

#endif
