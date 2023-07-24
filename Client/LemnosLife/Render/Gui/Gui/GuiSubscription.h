#ifndef DEF_GUISUBSCRIPTION
#define DEF_GUISUBSCRIPTION

#include "Gui.h"
#include <string>
#include <vector>
#include "Button.h"
#include "Textfield.h"

class GuiSubscription : public Gui
{
public:
    void initGui(), resizeGui(), renderGui();
    bool isDynamic(), button0Clicked = false;
private:
    double m_titleCenterY, m_titleWidthDiv2, m_titleHeightDiv2, m_topBackground, m_bottomBackground, m_leftBackground, m_rightBackground, m_titleHeightDiv4, m_heightText0;
    std::vector<Button> m_buttons;
    void onButton0Clicked();
};

extern bool waitingSubscription;

#endif
