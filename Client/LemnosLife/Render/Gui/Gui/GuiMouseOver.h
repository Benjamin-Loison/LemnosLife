#ifndef DEF_GUI_MOUSE_OVER
#define DEF_GUI_MOUSE_OVER

#include "Gui.h"
#include <vector>
#include <string>

class GuiMouseOver : public Gui
{
    public:
        void initGui(), resizeGui(), renderGui();
        std::vector<Button> m_buttons;
        std::string targetUsername = "";
    private:
        bool button0Clicked = false, button1Clicked = false, button2Clicked = false;
        void onButton0Clicked(), onButton1Clicked(), onButton2Clicked();
};

#endif
