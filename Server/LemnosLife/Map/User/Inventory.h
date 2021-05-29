#ifndef DEF_INVENTORY
#define DEF_INVENTORY

#include "../../../MathPlus/math_plus.h"
#include "View.h"

#include <string>
#include <vector>
#include <map>

#define HOTBAR_DEFAULT_SLOTS 2

#define DEFAULT_ITEM 0
#define DEFAULT_STACK 1
// DEFAULT_STACK used to be on 0 (when on client was 1)
#define DEFAULT_ITEM_NAME ""
#define DEFAULT_ITEM_SIZE 1

#define BACKPACK_WIDTH 3
#define BACKPACK_HEIGHT 3

//#define ITEMS_NUMBER 3
// isn't the above pre processor instruction obsolete ? it should !

enum foodAbility{FOOD_ABILITY_NO, FOOD_ABILITY_FOOD, FOOD_ABILITY_DRINK, FOOD_ABILITY_SMOKING}; // F, D, S (or is a drug for the moment)

class Item
{
    public:
        Item(/*unsigned int = DEFAULT_ITEM, */std::string = DEFAULT_ITEM_NAME, unsigned int = DEFAULT_STACK, unsigned short = DEFAULT_ITEM_SIZE, unsigned short = DEFAULT_ITEM_SIZE, foodAbility = FOOD_ABILITY_NO, double quantity = 0, std::string gunName = ""), Item(Item const&); // add weight
        const unsigned int getMaxStack(), getId();
        unsigned short getWidth(), getHeight();
        const std::string getName(), getAmmo();
        virtual ~Item() = default;
        foodAbility getFoodAbility();
        double getQuantity();
    protected:
        unsigned int m_id, m_maxStack;
        std::string m_name, m_ammo;
        unsigned short m_width, m_height;
        foodAbility m_foodAbility;
        double m_quantity;// unsigned double doesn't pay the bill (isn't worth)
};

Item* getItemPtr(std::string);

class Slot
{
    public:
        Slot();
        Slot(unsigned int itemId, unsigned int stack);
        Item* getItemPtr();
        unsigned int getStack();
        bool isEmpty(), setItem(unsigned int = DEFAULT_ITEM, unsigned int = DEFAULT_STACK, std::string username = ""), setItem(Slot*);
        void removeStack(unsigned int stack);
    private:
        Item m_item;
        Item* m_itemPtr;
        unsigned int m_stack;
};

bool hasFoodAbility(Slot*); // need to be declared after Slot lel

class Backpack : public Item
{
    public:
        Backpack(std::string, unsigned int, unsigned short, unsigned short), Backpack(Backpack const&), Backpack(std::string, unsigned int, std::string);
        unsigned short getStorageWidth(), getStorageHeight();
        bool setItemInSlot(Slot*, unsigned short, unsigned short), setItemInSlotExcept(Slot*, unsigned short, unsigned short, unsigned short = UNSIGNED_SHORT_MAX, unsigned short = UNSIGNED_SHORT_MAX), setItemInSlot(unsigned int itemId, unsigned int stack, unsigned short x, unsigned short y), isSlotAvailable(unsigned short x, unsigned short y);
        Slot* getSlotPtr(unsigned short, unsigned short);
        std::vector<Slot*> getNonNullSlots();
        unsigned int getSlotItem(unsigned short x, unsigned short y);
        std::vector<std::pair<unsigned short, unsigned short>> getNonNullSlotsIndexes();
        void clear();
    private:
        unsigned short m_storageWidth, m_storageHeight;
        std::map<std::pair<unsigned short, unsigned short>, Slot> m_storage;
};

extern std::vector<Item*> items;
extern std::map<std::string, unsigned int> itemsNames;

class Hotbar
{
    public:
        Hotbar();
        unsigned short getSlotsNumber(), getSelectedSlot();
        void setSelectedSlot(unsigned short);
    private:
        std::vector<std::pair<unsigned short, unsigned short>> m_slots;
        unsigned short m_selectedSlot;
};

class Inventory
{
    public:
        Inventory(), Inventory(std::string), Inventory(std::string username, std::string inventoryStr);
        Hotbar* getHotbarPtr();
        Slot* getHandPtr(), *getBackpackPtr();
        void setItemInHand(unsigned int = DEFAULT_ITEM, unsigned int = DEFAULT_STACK), setBackpack(unsigned int = DEFAULT_ITEM, unsigned int = DEFAULT_STACK, bool sync = true), setBackpack(Slot*), sendItemInHandInfo(bool onlyOtherPlayers = false), clear(), sendBackpackInfo(bool onlyOtherPlayers = false), sendBackpackStuffInfo(), clearBackpack();
        bool consumeAmmo(std::string gunName), addItem(unsigned int, unsigned int), containsItem(unsigned int), containsItem(std::string);
        std::string handToString(bool specifyUsername = true), backpackToString(bool specifyUsername = true);
    private:
        Hotbar m_hotbar;
        Slot m_hand, m_backpack;
        std::string m_username;
};

void initializeInventory(), addItemOnGround(View, unsigned int itemId, unsigned int stack, std::string username = ""/*default argument not used*/), addItemOnGround(View, Slot*, std::string username = ""), saveWallets(), saveItemsOnGround(), clearGround();
std::string getItemName(unsigned int), getItemNameLg(unsigned int), toString(Inventory), toString(Slot*), toStringBackpack(Backpack*, bool withSize), toStringBackpack(Slot*), toStringBackpackStuff(Item*, bool withSize = false), toStringBackpackStuff(Slot*), itemsOnGroundToString();
bool isAnItem(std::string), isAnItemNotConsideringCase(std::string), isAGun(Item*);
unsigned int addElement(std::map<unsigned int, std::tuple<View, unsigned int, unsigned int>>*, std::tuple<View, unsigned int, unsigned int>, unsigned int forceIndex = UNSIGNED_INT_MAX), getItemIdNotConsideringCase(std::string);

extern unsigned int itemsOnGroundIndex;
extern std::string itemsOnGroundFile;
extern /*std::vector<std::tuple<View, unsigned int, unsigned int>>*/std::map<unsigned int, std::tuple<View, unsigned int, unsigned int>> itemsOnGround; // used to use Position
extern std::map<std::string, std::map<unsigned int, std::pair<unsigned long long, unsigned long long>>> shopPrices;

#endif
