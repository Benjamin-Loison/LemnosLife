#ifndef DEF_GUIGAME
#define DEF_GUIGAME

#include "Gui.h"
#include <windows.h>
#include <wingdi.h>
#include <vector>

extern std::vector<std::vector<double>> debugLinesToInit;

class GuiGame : public Gui
{
    public:
        void initGui(), renderGui(), resizeGui();
        bool isDynamic();
    private:
        unsigned short crosshairBottomLeftX, crosshairBottomLeftY, crosshairTopRightX, crosshairTopRightY;
};

#endif
