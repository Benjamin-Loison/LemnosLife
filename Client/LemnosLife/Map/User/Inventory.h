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

///#define LOG_DEBUG_3D_ITEMS

//#define ITEMS_NUMBER 3

//extern std::string itemsNames[ITEMS_NUMBER];

enum foodAbility{FOOD_ABILITY_NO, FOOD_ABILITY_FOOD, FOOD_ABILITY_DRINK, FOOD_ABILITY_SMOKING}; // F, D, S (or is a drug for the moment)

class Item
{
    public:
        Item(/*unsigned int = DEFAULT_ITEM, */std::string = DEFAULT_ITEM_NAME, std::string = DEFAULT_ITEM_TEXTURE, unsigned int = DEFAULT_STACK, unsigned short = DEFAULT_ITEM_SIZE, unsigned short = DEFAULT_ITEM_SIZE, foodAbility = FOOD_ABILITY_NO, std::string ammo = ""), Item(Item const&); // add weight
        const unsigned int getMaxStack(), getId();
        unsigned short getWidth(), getHeight();
        const std::string getName(), getNameFromId(), getAmmo(), getTexture();
        virtual ~Item() = default;
        bool needDisplayStack();
        foodAbility getFoodAbility();
    protected:
        unsigned int m_id, m_maxStack;
        std::string m_name, m_ammo, m_texture;
        unsigned short m_width, m_height;
        foodAbility m_foodAbility;
};

Item* getItemPtr(std::string);

class Slot
{
    public:
        Slot();
        Item* getItemPtr();
        unsigned int getStack();
        void use(), stopUsing(), removeStack(unsigned int);
        bool isEmpty(), setItem(unsigned int = DEFAULT_ITEM, unsigned int = DEFAULT_STACK);
    private:
        Item m_item;
        Item* m_itemPtr;
        unsigned int m_stack;
};

class Backpack : public Item
{
    public:
        Backpack(); // seems to be required for non-initialize constructor which has one Backpack as an instance variable
        Backpack(std::string, std::string texture, unsigned int, unsigned short width, unsigned short height), Backpack(Backpack const&), Backpack(std::string, std::string, unsigned int, Backpack*), Backpack(std::string name, std::string texture, unsigned int maxStack, std::string content);
        unsigned short getStorageWidth(), getStorageHeight();
        bool setItemInSlot(Slot*, unsigned short, unsigned short), isSlotAvailable(unsigned short, unsigned short), setItemInSlot(unsigned int itemId, unsigned int stack, unsigned short x, unsigned short y),
             setItemInSlot(Slot*, std::pair<unsigned short, unsigned short>), isSlotAvailable(std::pair<unsigned short, unsigned short>);
        Slot* getSlotPtr(unsigned short, unsigned short), *getSlotPtr(std::pair<unsigned short, unsigned short>);
        std::pair<unsigned short, unsigned short> getSlotBackpack(unsigned short, unsigned short);
        unsigned int getSlotItem(unsigned short x, unsigned short y);
        void clear(), setStorageSize(unsigned short, unsigned short), setStorageSize(Backpack*), setContent(std::string contentStr);//, fillWith(Backpack*);
        std::vector<Slot*> getNonNullSlots();
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
        void setItemInHand(Slot*), setBackpack(unsigned int = DEFAULT_ITEM), setBackpack(Slot*), doHandRender(/*double phi = 360, double theta = 91*/);
        bool containsItem(unsigned int) /* not used for the moment as public */, containsItem(std::string), setItemInHand(unsigned int = DEFAULT_ITEM, unsigned int = DEFAULT_STACK), consumeAmmo(std::string, bool removeAmmo = false);
    private:
        Hotbar m_hotbar;
        Slot m_hand, m_backpack;
        std::string m_username;
};

void initializeInventory(),
     addElement(std::map<unsigned int, std::tuple<View, unsigned int, unsigned int>>*, std::tuple<View, unsigned int, unsigned int>),
     freeInventory(),
     clearGround();
std::string getItemName(unsigned int), getItemNameLg(unsigned int);
//extern std::map<unsigned int, Gl_object> items3DDbg1;
//extern std::map<unsigned int, Structure> items3DDbg0;
extern std::map<unsigned int, DynamicGl_object> items3D;
extern unsigned int itemInHandRenderId;
//extern bool stuffInHands, justRemoved;
bool isABackpack(unsigned int itemId), isAGun(Slot*), isAGun(unsigned int itemId);
extern std::map<unsigned int, std::tuple<double, double, double>> itemSizes;

//extern std::vector<std::tuple<View, unsigned int, unsigned int>> itemsOnGround; // used to use Position (so no rotation)
extern std::map<unsigned int, std::tuple<View, unsigned int, unsigned int>> itemsOnGround;

#endif
