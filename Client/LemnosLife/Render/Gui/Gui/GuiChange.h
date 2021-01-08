#ifndef DEF_GUICHANGE
#define DEF_GUICHANGE

#include "Gui.h"
#include <string>
#include <vector>
#include "Button.h"
#include "Textfield.h"

class GuiChange : public Gui
{
    public:
        void initGui(), resizeGui(), renderGui();
        bool isDynamic(), button0Clicked = false, button1Clicked = false;
        std::vector<Textfield> m_textfields;
    private:
        double m_titleCenterY, m_titleWidthDiv2, m_titleHeightDiv2, m_titleHeightDiv4, m_topBackground, m_bottomBackground, m_leftBackground, m_rightBackground, m_heightText0, m_heightText1, m_heightText2, m_heightText3, m_heightText4, m_heightText5, m_widthText0;
        std::vector<Button> m_buttones;
        std::string m_errorMessage;
        void onButton0Clicked(), onButton1Clicked();
};


#endif
