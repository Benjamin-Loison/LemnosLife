#ifndef DEF_GUISERVERS
#define DEF_GUISERVERS

#include <vector>
#include "Gui.h"
#include "Button.h"
#include <thread>

#define ARMA_3_REQUIRED " (Arma 3 required)"

//extern std::string serverName;
extern std::thread loadMainMenuThread;

class GuiServers : public Gui
{
public:
    void initGui(), renderGui(), resizeGui();
    bool isDynamic(), buttonClicked = false;
private:
    std::vector<Button> m_buttons;
    double m_titleWidthDiv2;
    void connectTo(unsigned short serversIndex = 0), onButtonClicked();
};

#endif
