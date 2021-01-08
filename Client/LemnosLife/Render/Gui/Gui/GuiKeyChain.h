#ifndef DEF_GUIKEYCHAIN
#define DEF_GUIKEYCHAIN

#include "Gui.h"
#include <vector>
#include <string>

class GuiKeyChain : public Gui
{
    public:
        void initGui(), resizeGui(), renderGui();
        bool button0Clicked = false, button1Clicked = false, button2Clicked = false;
    private:
        double m_topMenu, m_rightMenu, m_leftMenuIn, m_rightMenuIn, m_topMenuIn, m_bottomMenuIn, m_middleMoneyStatsX, m_middleMenuInY, m_leftMenuMiddle, m_rightMenuMiddle, m_bottomFirstButton;
        std::vector<Button> m_buttons;
        std::vector<Radio> m_radios;
        void onButton0Clicked(), onButton1Clicked(), onButton2Clicked(), initTemporaryGui();
};

#endif
