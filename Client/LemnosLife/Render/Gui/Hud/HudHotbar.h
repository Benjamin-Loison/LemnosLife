#ifndef DEF_HUD_HOTBAR
#define DEF_HUD_HOTBAR

#include "../Gui/Gui.h"

class HudHotbar : public Gui
{
public:
    void renderGui(), resizeGui();
    bool isDynamic();
private:
    double m_slotSize, m_slotSizeDiv2, m_slotSizeDiv3, m_slotSizeDiv6, m_spaceBetween, m_spaceBetweenDiv2;
};

extern bool displayHotbar;

#endif
