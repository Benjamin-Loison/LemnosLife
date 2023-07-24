#ifndef DEF_GUISTEAM
#define DEF_GUISTEAM

#include "Gui.h"
#include <string>
#include <vector>
#include "Button.h"
#include "Textfield.h"

class GuiSteam : public Gui
{
public:
    void initGui(), resizeGui(), renderGui();
    bool isDynamic(), button0Clicked = false, button1Clicked = false;
    std::vector<Textfield> m_textfields;
private:
    double m_titleCenterY, m_titleWidthDiv2, m_titleHeightDiv2, m_topBackground, m_bottomBackground, m_leftBackground, m_rightBackground, m_titleHeightDiv4, m_heightText0;
    std::vector<Button> m_buttons;
    std::string errorMessage;
    void onButton0Clicked(), onButton1Clicked();
};

extern bool waitingSteam;

#endif
