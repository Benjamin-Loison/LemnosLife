#ifndef DEF_GUISPAWN
#define DEF_GUISPAWN

#include "Gui.h"
#include <vector>
#include <string>

class GuiSpawn : public Gui
{
public:
    void initGui(), resizeGui(), renderGui();
    bool button0Clicked = false;
private:
    std::vector<Button> m_buttons;
    void onButton0Clicked();
    std::vector<Radio> m_radios;
};

#endif
