#ifndef DEF_GUIECHAP
#define DEF_GUIECHAP

#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/gl.h>
#include <vector>
#include "Gui.h"
#include "Button.h"

class GuiEchap : public Gui
{
    public:
        void initGui(), renderGui(), resizeGui();
        bool button0Clicked = false, button1Clicked = false, button2Clicked = false, button3Clicked = false;
    private:
        std::vector<Button> m_buttons;
        double m_titleCenterY, m_titleWidthDiv2, m_titleHeightDiv2;
        void onButton0Clicked(), onButton1Clicked(), onButton2Clicked(), onButton3Clicked();
};

extern bool reconnectingToTheServer, disconnecting;
void disconnect(std::string = "", std::string = "");

#endif
