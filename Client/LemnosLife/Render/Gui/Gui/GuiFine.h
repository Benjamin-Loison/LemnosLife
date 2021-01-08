#ifndef DEF_GUIFINE
#define DEF_GUIFINE

#include "Gui.h"
#include <vector>
#include <string>

class GuiFine : public Gui
{
    public:
        void initGui(), resizeGui(), renderGui();
        std::vector<Button> m_buttons;
        std::vector<Textfield> m_textfields;
        std::string targetUsername;
    private:
        bool button0Clicked = false, button1Clicked = false;
        void onButton0Clicked(), onButton1Clicked();
};

#endif
