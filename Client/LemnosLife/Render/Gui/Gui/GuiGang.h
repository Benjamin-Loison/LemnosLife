#ifndef DEF_GUIGANG
#define DEF_GUIGANG

#include "Gui.h"
#include <vector>
#include <string>

class GuiGang : public Gui
{
public:
    void resizeGui(), renderGui();
    std::string chief, gang;
    std::vector<std::string> members;
    unsigned int money;
private:
    double m_bottom, m_top, m_left, m_right;
    void onButton0Clicked(), onButton1Clicked(), onButton2Clicked(), onButton3Clicked();
    std::vector<Textfield> m_textfields;
};

#endif
