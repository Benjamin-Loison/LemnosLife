#ifndef DEF_INVENTORY
#define DEF_INVENTORY

#include <string>
#include <vector>
#include <map>

#include "../Position.h"
#include "View.h"

#define HOTBAR_DEFAULT_SLOTS 2

#define DEFAULT_ITEM 0
#define DEFAULT_STACK 1
#define DEFAULT_ITEM_NAME ""
#define DEFAULT_ITEM_TEXTURE ""
#define DEFAULT_ITEM_SIZE 1

#define BACKPACK_WIDTH 3
#define BACKPACK_HEIGHT 3

#define BACKPACK_HOTBAR 2

#define DEFAULT_HOTBAR_SELECTION 1

#include "../Structure.h"
#include "../../../MathPlus/math_plus.h"

///#define LOG_DEBUG_3D_ITEMS

enum foodAbility {FOOD_ABILITY_NO, FOOD_ABILITY_FOOD, FOOD_ABILITY_DRINK, FOOD_ABILITY_SMOKING}; // F, D, S (or is a drug for the moment)

class Item
{
public:
    Item(/*unsigned int = DEFAULT_ITEM, */std::string = DEFAULT_ITEM_NAME, std::string = DEFAULT_ITEM_TEXTURE, unsigned int = DEFAULT_STACK, unsigned short = DEFAULT_ITEM_SIZE, unsigned short = DEFAULT_ITEM_SIZE, foodAbility = FOOD_ABILITY_NO, std::string ammo = "", bool force = false), Item(Item const&); // add weight
    const unsigned int getMaxStack(), getId();
    unsigned short getWidth(), getHeight();
    const std::string getName(), getNameFromId(), getAmmo(), getTexture(), itemToString();
    virtual ~Item() = default;
    bool needDisplayStack();
    foodAbility getFoodAbility();
protected: // well maybe not everything as protected ?
    unsigned int m_id, m_maxStack;
    std::string m_name, m_ammo, m_texture;
    unsigned short m_width, m_height;
    foodAbility m_foodAbility;
};

Item* getItemPtr(std::string);

class Slot
{
public:
    Slot(unsigned int itemId = DEFAULT_ITEM, unsigned int itemStack = DEFAULT_STACK);
    Item* getItemPtr();
    unsigned int getStack();
    void use(), stopUsing(), removeStack(unsigned int), clear();
    bool isEmpty(), setItem(unsigned int = DEFAULT_ITEM, unsigned int = DEFAULT_STACK);
    std::string slotToString(); // if named toString it doesn't work somewhere else in the program at least for item or slot or backpack or foodAbility
private:
    Item m_item;
    Item* m_itemPtr; /// should add a destructor to delete this at the end of use of slot
    unsigned int m_stack;
};

class Backpack : public Item
{
public:
    Backpack(); // seems to be required for non-initialize constructor which has one Backpack as an instance variable
    Backpack(std::string, std::string texture, unsigned int, unsigned short width, unsigned short height), Backpack(Backpack const&), Backpack(std::string, std::string, unsigned int, Backpack*), Backpack(std::string name, std::string texture, unsigned int maxStack, std::string content);
    unsigned short getStorageWidth(), getStorageHeight();
    bool setItemInSlotExcept(Slot*, unsigned short, unsigned short, unsigned short = UNSIGNED_SHORT_MAX, unsigned short = UNSIGNED_SHORT_MAX, bool = true), setItemInSlotSlot(Slot*, unsigned short, unsigned short, bool = true), isSlotAvailable(unsigned short, unsigned short, unsigned short xExcept = UNSIGNED_SHORT_MAX, unsigned short yExcept = UNSIGNED_SHORT_MAX),
         setItemInSlot(unsigned int itemId, unsigned int stack, unsigned short x, unsigned short y), setItemInSlot(Slot*, std::pair<unsigned short, unsigned short>, std::pair<unsigned short, unsigned short> = /*make_pair(*/ {UNSIGNED_SHORT_MAX, UNSIGNED_SHORT_MAX}/*)*/), isSlotAvailable(std::pair<unsigned short, unsigned short>), addItem(/*Item**/Slot*, unsigned short*, unsigned short*, bool = true),
         setItemInSlotSlot(unsigned int itemId, unsigned int itemStack, std::pair<unsigned short, unsigned short> coordinates, std::pair<unsigned short, unsigned short> coordinatesExcepted = std::make_pair(UNSIGNED_SHORT_MAX, UNSIGNED_SHORT_MAX), bool checkAvailability = true);//,
    //setItemInSlotSlot(unsigned int itemId, unsigned int itemStack, std::pair<unsigned short, unsigned short> coordinates, unsigned short coordinatesXExcepted = UNSIGNED_SHORT_MAX, unsigned short coordinatesYExcepted = UNSIGNED_SHORT_MAX, bool checkAvailability = true);
    Slot* getSlotPtr(unsigned short, unsigned short), *getSlotPtr(std::pair<unsigned short, unsigned short>), *getSlotPtrRoughly(unsigned short x, unsigned short y, unsigned short xExcept = UNSIGNED_SHORT_MAX, unsigned short yExcept = UNSIGNED_SHORT_MAX), *getSlotPtrRoughly(std::pair<unsigned short, unsigned short>);
    std::pair<unsigned short, unsigned short> getSlotBackpack(unsigned short, unsigned short), getSlotBackpack(std::pair<unsigned short, unsigned short>), getCoordinatesForSlot(Slot* slotNeedle);
    unsigned int getSlotItem(unsigned short x, unsigned short y, unsigned short xExcept = UNSIGNED_SHORT_MAX, unsigned short yExcept = UNSIGNED_SHORT_MAX);
    void clear(), setStorageSize(unsigned short, unsigned short), setStorageSize(Backpack*), setContent(std::string contentStr);//, fillWith(Backpack*);
    std::vector<Slot*> getNonNullSlots();
    std::string backpackToString();
private:
    unsigned short m_storageWidth, m_storageHeight; // could also make 2-dimmensionnal table with maximum size and check for storageWidth and storageHeight when working on it
    std::map<std::pair<unsigned short, unsigned short>, Slot> m_storage;
};

extern std::vector<Item*> items;
extern std::map<std::string, unsigned int> itemsNames;
extern std::vector<unsigned int> backpackIds; // isn't used as external

class Hotbar
{
public:
    Hotbar();
    unsigned short getSlotsNumber(), getSelectedSlot();
    void setSelectedSlot(unsigned short), addSlots(unsigned short), removeSlots(unsigned short);
private:
    std::vector<std::pair<unsigned short, unsigned short>> m_slots;
    unsigned short m_selectedSlot;
};

class Inventory
{
public:
    Inventory(std::string username = "");
    Hotbar* getHotbarPtr();
    Slot* getHandPtr(), *getBackpackPtr();
    void setItemInHand(Slot*), setBackpack(unsigned int = DEFAULT_ITEM/*, bool forceRemoveRender = false*/), setBackpack(Slot*), doHandRender(/*double phi = 360, double theta = 91*/), doBackpackRender(), clear();
    bool containsItem(unsigned int) /* not used for the moment as public */, containsItem(std::string), setItemInHand(unsigned int = DEFAULT_ITEM, unsigned int = DEFAULT_STACK), consumeAmmo(std::string, bool removeAmmo = false), isHoldingASniper(), isHoldingBinoculars();
private:
    void setBackpackCommon(/*bool forceRemoveRender = false*/);
    Hotbar m_hotbar;
    Slot m_hand, m_backpack;
    std::string m_username;
};

void initializeInventory(),
     addElement(std::map<unsigned int, std::tuple<View, unsigned int, unsigned int>>*, std::tuple<View, unsigned int, unsigned int>, unsigned int = UNSIGNED_INT_MAX),
     freeInventory(),
     clearGround(),
     loadAll3DItems();
std::string getItemName(unsigned int), getItemNameLg(unsigned int), itemsOnGroundToString(), foodAbilityToString(foodAbility);
//extern std::map<unsigned int, Gl_object> items3DDbg1;
//extern std::map<unsigned int, Structure> items3DDbg0;
extern std::map<unsigned int, DynamicGl_object> items3D;
extern unsigned int itemsOnGroundIndex;
//extern unsigned int itemInHandRenderId;
//unsigned int getItemInHandRenderId();
//extern bool stuffInHands, justRemoved;
bool isABackpack(unsigned int itemId), isAGun(Slot*), isAGun(unsigned int itemId);
extern std::map<unsigned int, std::tuple<double, double, double>> itemSizes;

//extern std::vector<std::tuple<View, unsigned int, unsigned int>> itemsOnGround;
extern std::map<unsigned int, std::tuple<View, unsigned int, unsigned int>> itemsOnGround;
unsigned int getItemId(std::string itemName);

#endif
