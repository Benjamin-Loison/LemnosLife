#ifndef DEF_GUIMAINMENU
#define DEF_GUIMAINMENU

#define GLEW_STATIC
#include <glew.h>
#include <gl.h>
#include <vector>
#include "Gui.h"
#include "Button.h"

class GuiMainMenu : public Gui
{
    public:
        void initGui(), renderGui(), resizeGui();
        bool isDynamic();
    private:
        GLuint m_mainMenuBackgroundTexture;
        std::vector<Button> buttons;
};

#endif
