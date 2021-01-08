#ifndef DEF_GUIPHONE
#define DEF_GUIPHONE

#include "Gui.h"
#include <vector>
#include <string>

class GuiPhone : public Gui
{
    public:
        void initGui(), resizeGui(), renderGui();
        bool button0Clicked = false, button1Clicked = false, button2Clicked = false, button3Clicked = false, button4Clicked = false, button5Clicked = false, button6Clicked = false, button7Clicked = false, button8Clicked = false;
        std::vector<Textfield> m_textfields;
    private:
        double m_topMenu, m_rightMenu, m_leftMenuIn, m_rightMenuIn, m_topMenuIn, m_bottomMenuIn, m_middleMenu, m_middleMenuInY, m_barWidthDiv2, m_ySubtitle;
        std::vector<Button> m_buttons;
        std::vector<Radio> m_radios;
        void onButton0Clicked(), onButton1Clicked(), onButton2Clicked(), onButton3Clicked(), onButton4Clicked(), onButton5Clicked(), onButton6Clicked(), onButton7Clicked(), onButton8Clicked();
        bool messageSent(std::string from, std::string to/*, std::string grade = ""*/);
};

#endif
