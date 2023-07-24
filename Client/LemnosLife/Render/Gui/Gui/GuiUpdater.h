#ifndef DEF_GUIUPDATER
#define DEF_GUIUPDATER

#include "Gui.h"
#include <string>
#include <vector>
#include "Button.h"

extern std::string updateLine, unit, updaterURL;
extern double amountDownloaded, amountToDownload, progress, unitDiv; // why using a double ? - ah maybe for dividing correctly size by 1000 etc
extern bool downloadInit;

class GuiUpdater : public Gui
{
public:
    void initGui(), resizeGui(), renderGui();
    bool isDynamic(), button0Clicked = false;
private:
    std::vector<Button> m_buttons;
    void onButton0Clicked();
};

#endif
