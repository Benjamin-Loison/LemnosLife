#ifndef DEF_GUIMAINMENU
#define DEF_GUIMAINMENU

#define GLEW_STATIC
#include <GL/glew.h>
#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif
#include <vector>
#include "Gui.h"
#include "Button.h"

class GuiMainMenu : public Gui
{
public:
    void initGui(), renderGui(), resizeGui();
    bool isDynamic(), button0Clicked = false, button1Clicked = false, button2Clicked = false, button3Clicked = false, button4Clicked = false, button5Clicked = false;
private:
    std::vector<Button> m_buttons;
    double m_titleCenterY, m_titleWidthDiv2, m_titleWidthDiv4, m_titleWidthDiv8, m_titleHeightDiv2, m_titleHeightDiv4, windowWidthDiv4, m_titleCenterYError;
    void onButton0Clicked(), onButton1Clicked(), onButton2Clicked(), onButton3Clicked(), onButton4Clicked(), onButton5Clicked();
};

extern bool launchingGame, connectingToServer;
extern std::string errorMessageGuiMainMenu, errorMessageGuiMainMenuTmp;

#endif
