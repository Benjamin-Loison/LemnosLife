#ifndef DEF_GUILEMNOSINVENTORY
#define DEF_GUILEMNOSINVENTORY

#include "Gui.h"
#include <vector>
#include <string>

class GuiLemnosInventory : public Gui
{
public:
    void initGui(), resizeGui(), renderGui();
    bool button0Clicked = false, button1Clicked = false, button2Clicked = false, button3Clicked = false, button4Clicked = false;
    std::vector<Textfield> m_textfields;
private:
    double m_topMenu, m_rightMenu, m_leftMenuIn, m_rightMenuIn, m_topMenuIn, m_bottomMenuIn, m_middleMoneyStatsX, m_middleMenuInY, m_leftMenuMiddle, m_rightMenuMiddle, m_middleLicensesX, m_bottomFirstButton, m_rightIconLeft, m_topIconATMLeft,
           m_bottomIconATMLeft, m_middleIconATMLeft, m_topIconDollarsLeft, m_bottomIconDollarsLeft, m_amountMiddleX, m_amountWidthDiv2, m_middleIconDollarsLeft, m_topLicense;
    std::vector<Radio> m_radios;
    std::vector<Button> m_buttons;
    std::vector<TextBox> m_textboxes;
    void onButton0Clicked(), onButton1Clicked(), onButton2Clicked(), onButton3Clicked(), onButton4Clicked(), resetUsernames(), updateUsernames();
};

//extern bool needUpdateUsernames;

#endif
