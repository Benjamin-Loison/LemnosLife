#include <string>

#include "../../../Main/main.h"
#include "../../Engine/engine.h"
#include "../../../../Logger/logger.h"
#include "../../../../3D/Render/Engine/sdlglutils.h"
#include "../../Engine/textureManager.h"
#include "GuiMainMenu.h"
#include "Gui.h"
using namespace std;

double titleCenterY, titleWidthDiv2, titleHeightDiv2;

void GuiMainMenu::initGui()
{
    m_mainMenuBackgroundTexture = addGetTexture(string(picturesFolder + "background.jpg"), "loadNormalTexture");
    buttons.push_back(Button("game", "arial", 0, 0, 0, 0, 0));
}

void GuiMainMenu::renderGui()
{
    displayPicture(m_mainMenuBackgroundTexture, 0, 0, windowWidth, windowHeight);
    displayText("mainMenuTitle", windowWidthDiv2, titleCenterY, titleWidthDiv2, titleHeightDiv2, name);

    //Display buttons
    for(int i = 0; i < buttons.size(); i++)
        buttons[i].render();
}

void GuiMainMenu::resizeGui()
{
    titleWidthDiv2 = windowWidth / 5;
    titleHeightDiv2 = windowHeight / 10;
    titleCenterY = windowHeight - titleHeightDiv2 - titleHeightDiv2 / 5;
    if(buttons.size() > 0)
        buttons[0].resize(windowWidthDiv2, windowHeightDiv2, titleWidthDiv2 * 2, titleHeightDiv2);
}

bool GuiMainMenu::isDynamic()
{
    return true;
}
