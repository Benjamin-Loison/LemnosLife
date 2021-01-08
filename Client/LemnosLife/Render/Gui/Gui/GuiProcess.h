#ifndef DEF_GUIPROCESS
#define DEF_GUIPROCESS

#include "Gui.h"
#include <vector>
#include <string>

class GuiProcess : public Gui // would also be used for buying licenses (make licenses as items #Ultra HardCore ? - Not now at least)
{
    public:
        void initGui(), resizeGui(), renderGui();
    private:
        std::vector<Button> m_buttons;
        std::vector<Radio> m_radios;
        void onButton0Clicked(), onButton1Clicked();
        bool button0Clicked = false, button1Clicked = false;
        double m_leftMenu, m_topMenu, m_rightMenu;
};

// button name + action
// list to display
// need textfield for process

#endif
