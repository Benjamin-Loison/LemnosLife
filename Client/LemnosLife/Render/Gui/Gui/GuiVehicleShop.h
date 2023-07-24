#ifndef DEF_GUIVEHICLESHOP
#define DEF_GUIVEHICLESHOP

#include "Gui.h"

#include <vector>
#include <string>

extern std::string vehicleShopName, npcName;

class GuiVehicleShop : public Gui
{
public:
    void initGui(), resizeGui(), renderGui();
    unsigned int getVehicleIndex(std::string vehicleNameToFind), getTextureIndex(std::string vehicleId, std::string vehicleTextureToFind);
    std::vector<Radio> m_radios;
private:
    std::vector<Button> m_buttons;
    void onButton0Clicked(), onButton1Clicked();
    bool button0Clicked = false, button1Clicked = false;
    double m_leftMenu, m_topMenu, m_rightMenu;
};

#endif
