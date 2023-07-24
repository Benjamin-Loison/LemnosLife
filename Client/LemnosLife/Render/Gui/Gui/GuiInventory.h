#ifndef DEF_GUI_INVENTORY
#define DEF_GUI_INVENTORY

#include "Gui.h"
#include <vector>
#include <string>
//#include "../../../Map/User/Inventory.h"
#include "../../../../Vehicles/Vehicle.h"

class GuiInventory : public Gui
{
public:
    void initGui(), resizeGui(), renderGui(), drawSlot(double, double), drawSlots(unsigned short height, unsigned short width, unsigned short xMin, unsigned short xMax, unsigned short y, bool isShop = false/*, bool boolFunction = nullptr*/), drawHands(double = 0), drawBackpackContent(Backpack*, double, double, double, unsigned short, bool = false), drawItemOnFly(Slot*), drawHandsBackground(double), select(unsigned short), resetSelection(),
         refreshMouseCoordinates(), refreshSelection(unsigned short, double = 0, Backpack* = nullptr), addToDrawItemOnFly(Slot* slot), drawItemsOnFly();
    bool isMouseInHands(double = 0), isMouseInBackpackSlot(), isMouseInBackpackSlots(Backpack*), isMouseInVicinity(), isShop, isVehicle, isPlayer, isMouseInShop();
    std::pair<unsigned short, unsigned short> getSlotSelectByMouseInBackpack(Backpack*, double, double);
private:
    void displaySlot(Slot*, double, double, double, double, bool = false, bool = true, bool = false);
    double m_slotSize, m_middleLeft, m_middleRight, m_middleBetween, m_middleTop0, m_middleHand, m_middleHands, m_middleTop1, m_leftLeft, m_leftRight, m_sideTop, m_sideBottom0, m_sideBottom1, m_leftMiddleHori, m_sideMiddleVerti0, m_sideMiddleVerti1, m_rightLeft,
           m_rightRight, m_rightMiddleHori, m_rightBetween0, m_middleWidth, m_topVicinity, m_bottomTitleVicinity, m_bottomVicinity; // use double and not unsigned short because otherwise can be accumulated computation errors/approximations
};

extern Backpack* shopBackpack;
void setShopBackpack(std::string shopName, bool forceSize = false), setPlayerBackpack(std::string content);
extern std::string shopName;
extern Vehicle* shopVehiclePtr;

#endif
