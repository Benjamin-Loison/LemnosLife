#ifndef DEF_GUI2FA
#define DEF_GUI2FA

#include "Gui.h"
#include <string>
#include <vector>
#include "Button.h"
#include "Textfield.h"

class Gui2FA : public Gui
{
    public:
        void initGui(), resizeGui(), renderGui();
        bool isDynamic(), button0Clicked = false, button1Clicked = false;
        std::vector<Textfield> m_textfields;
    private:
        double m_titleCenterY, m_titleWidth, m_titleWidthDiv2, m_titleHeightDiv2, m_titleHeightDiv4, m_topBackground, m_bottomBackground, m_leftBackground, m_rightBackground, m_heightText0, m_widthText0, m_heightText1, m_heightText2, m_titleWidthMul1Dot5, m_heightText3,
               m_heightText4, m_heightText5, m_errorMessageY;
        std::vector<Button> m_buttones;
        void onButton0Clicked(), onButton1Clicked();
        enum state{NONE, ENABLING_PROPOSITION, ENABLING_CONFIRMATION, DISABLING_CONFIRMATION};
        state m_state = NONE;
        std::string m_key, m_errorMessage;
};


#endif
