#ifndef DEF_GUINAME
#define DEF_GUINAME

#include "Gui.h"
#include <string>
#include <vector>
#include "Button.h"
#include "Textfield.h"

class GuiName : public Gui
{
    public:
        void initGui(), resizeGui(), renderGui();
        bool isDynamic(), button0Clicked = false;
        std::vector<Textfield> m_textfields;
    private:
        double m_titleCenterY, m_titleWidthDiv2, m_titleHeightDiv2, m_topBackground, m_bottomBackground, m_leftBackground, m_rightBackground, m_titleHeightDiv4, m_heightText0, m_heightText1, m_heightText2, m_widthText0;
        std::vector<Button> m_buttones;
        std::string m_errorMessage, m_savedFirstName = "", m_savedLastName = "";
        void onButtonClicked();
};


#endif
