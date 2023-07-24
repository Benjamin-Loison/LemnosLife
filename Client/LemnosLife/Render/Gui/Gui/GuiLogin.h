#ifndef DEF_GUILOGIN
#define DEF_GUILOGIN

#include "Gui.h"
#include <string>
#include <vector>
#include "Button.h"
#include "Textfield.h"

class GuiLogin : public Gui
{
public:
    void initGui(), resizeGui(), renderGui();
    bool isDynamic(), button0Clicked = false, button1Clicked = false, requires2FA = false;
    std::vector<Textfield> m_textfields;
private:
    double m_titleCenterY, m_titleWidthDiv2, m_titleWidthDiv4, m_titleHeightDiv2, m_titleHeightDiv4, m_topBackground, m_bottomBackground, m_leftBackground, m_rightBackground, m_heightText0, m_heightText1, m_heightText2, m_heightText3, m_heightText4;
    std::vector<Button> m_buttons;
    std::string m_errorMessage;
    void onButtonClicked();
};


#endif
