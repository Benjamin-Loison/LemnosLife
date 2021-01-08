#ifndef DEF_GUIDEATH
#define DEF_GUIDEATH

#include "Gui.h"
#include <vector>
#include <string>

class GuiDeath : public Gui
{
    public:
        void initGui(), resizeGui(), renderGui();
    private:
        std::vector<Button> m_buttons;
        bool button0Clicked, button1Clicked, helpRequestAlreadySent;
        void onButton0Clicked(), onButton1Clicked(); // don't need () ? O_o - doch ...
};

#endif
