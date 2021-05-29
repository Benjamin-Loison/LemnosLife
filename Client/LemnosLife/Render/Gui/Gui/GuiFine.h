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
        bool button0Clicked = false, button1Clicked = false, button2Clicked;
    private:
        void onButton0Clicked(), onButton1Clicked(), onButton2Clicked();
};

extern unsigned long long amountFine;
extern std::string reasonFine, targetUsernameFine;

#endif
