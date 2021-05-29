#ifndef DEF_GUIATM
#define DEF_GUIATM

#include "Gui.h"
#include <vector>
#include <string>

class GuiATM : public Gui
{
    public:
        void initGui(), resizeGui(), renderGui();
        std::vector<Textfield> m_textfields;
    private:
        std::vector<Button> m_buttons;
        std::vector<Radio> m_radios;
        void onButton0Clicked(), onButton1Clicked(), onButton2Clicked(), onButton3Clicked(), onButton4Clicked(), onButton5Clicked(), updateUsernames()/*, resetUsernames()*/;
        bool button0Clicked = false, button1Clicked = false, button2Clicked = false, button3Clicked = false, button4Clicked = false, button5Clicked = false;
        double m_leftMenu, m_topMenu, m_rightMenu, m_leftMenuIn, m_topIconATMLeft, m_bottomIconATMLeft, m_rightIconLeft, m_amountMiddleX, m_middleIconATMLeft, m_middleIconDollarsLeft, m_amountWidthDiv2, m_bottomIconDollarsLeft, m_topIconDollarsLeft;
        unsigned long long getATMAmount();
};

#endif
