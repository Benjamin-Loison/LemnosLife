#ifndef DEF_GUIOPTIONS
#define DEF_GUIOPTIONS

#include <vector>
#include "Gui.h"
#include "Button.h"

class GuiOptions : public Gui
{
    public:
        void initGui(), renderGui(), resizeGui();
        bool isDynamic(), button0Clicked = false, button1Clicked = false, button2Clicked = false;
        std::vector<Textfield> m_textfields;
    private:
        void addBoolButton(std::string option, std::string toDisplay), addKeyButton(std::string option, std::string toDisplay), addDropDownButton(std::string option, std::string toDisplay),
             addRangeButton(std::string option, std::string toDisplay), resizeVariables(), onButton0Clicked(), onButton1Clicked(), onButton2Clicked();
        std::vector<Button> m_buttons;
        double defaultX, defaultY, defaultWidth, defaultHeight, defaultHeightDiv2, defaultHeightDiv4, quarter, spaceBetweenLines, widthBackgroundDiv2;
};

extern bool waitingKey;
extern long long newKey;

#endif
