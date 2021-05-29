#ifndef DEF_USER
#define DEF_USER

#include <string>
#include "View.h"
#include "../map.h"
#include "../../Main/main.h"
#include "../../../FilePlus/file_plus.h"
#include "../../../Collisions/Vector3D.h"
#include "../../../Collisions/3D.h"
#include "../../../Animation/Animation.h"
#include "Inventory.h"
#include <map>

// these maximum values can't be equal to UNSIGNED_SHORT_MAX otherwise syncHealth like function may have problems (and should use buffer variable)
#define MAX_HEALTH 100
#define MAX_FOOD 100
#define MAX_DRINK 100
#define MAX_BLEEDING 100
#define MAX_BREAK_BONE 206

#define MIN_HEALTH 0
#define MIN_FOOD 0
#define MIN_DRINK 0
#define MIN_BLEEDING 0
#define MIN_BREAK_BONE 0

#define DEFAULT_HEALTH 100
#define DEFAULT_REGEN 100
#define DEFAULT_FOOD 100
#define DEFAULT_DRINK 100
#define DEFAULT_BLEEDING 0
#define DEFAULT_BREAK_BONE 0
#define DEFAULT_STAMINA 100

#define CIVILIAN_ADM 0
#define HELPER_ADM 1
#define MODERATOR_ADM 2
#define ADMINISTRATOR_ADM 3
#define DEVELOPER_ADM 4
#define FONDATOR_ADM 5
#define HOST_ADM 6
#define ADM_NUMBER 7
extern std::string adminGrades[ADM_NUMBER];

#define CIVILIAN_POLICE 0
#define ADJOINT_POLICE 1
#define BRIGADIER_POLICE 2
#define SERGENT_POLICE 3
#define ADJUDANT_POLICE 4
#define MAJOR_POLICE 5
#define ASPIRANT_POLICE 6
#define LIEUTENANT_POLICE 7
#define CAPITAINE_POLICE 8
#define COMMANDANT_POLICE 9
#define COLONEL_POLICE 10
#define GENERAL_POLICE 11
#define POLICE_NUMBER 12
extern std::string policeGrades[POLICE_NUMBER];

#define CIVILIAN_JOB 0
#define REBEL_JOB 1
#define DOCTOR_JOB 2
#define REPAIRMAN_JOB 3
#define JOURNALIST_JOB 4
#define TAXI_JOB 5
#define JOB_NUMBER 6
extern std::string jobGrades[JOB_NUMBER];

#define CIVILIAN_VIP 0
#define VIP_VIP 1
#define VIPP_VIP 2
#define CHOUQUETTE_FOURREE_VIP 3
#define BAGUETTE_PREMIUM_VIP 4
#define BAGUETTE_TRADITION_VIP 5
#define VIP_NUMBER 7
extern std::string vipGrades[VIP_NUMBER];

#define LICENSE_DRIVE 0
#define LICENSE_BOAT 1
#define LICENSE_TRUCK 2
#define LICENSE_PILOT 3
#define LICENSE_DIVING 4
#define LICENSE_GUN 5
#define LICENSE_HOUSING 6
#define LICENSE_IRON 7
#define LICENSE_COPPER 8
#define LICENSE_GLASS 9
#define LICENSE_PETROL 10
#define LICENSE_CEMENT 11
#define LICENSE_SALT 12
#define LICENSE_DIAMAND 13
#define LICENSE_GOLD 14
#define LICENSE_PLATINUM 15
#define LICENSE_BEER 16
#define LICENSE_HEROIN 17
#define LICENSE_METH 18
#define LICENSE_COCAINE 19
#define LICENSE_CANNABIS 20
#define LICENSE_CIGARETTE 21
#define LICENSE_CIGAR 22
#define LICENSE_VODKA 23
#define LICENSE_REBEL 24
#define LICENSE_NUMBER 25
extern std::string licensesNames[LICENSE_NUMBER];

#define UNSIGNED_SHORT_MIN 0

// give basic money amount - done
// used to be 2.7
#define DEFAULT_SPEED 1
#define DEFAULT_FLY false
#define DEFAULT_ADMIN 0
#define DEFAULT_POLICE 0
#define DEFAULT_VIP 0
#define DEFAULT_JOB 0
#define DEFAULT_BAC false
#define DEFAULT_LICENSES "0000000000000000000000000"
#define DEFAULT_LICENSE false
#define DEFAULT_MONEY 0
#define DEFAULT_MONEYATM 0
#define DEFAULT_GANG ""
#define DEFAULT_GOD false
#define DEFAULT_VANISH false
#define DEFAULT_CUFFED false
#define DEFAULT_ESCORTED ""
#define DEFAULT_ESCORTING ""
//#define DEFAULT_STAMINA 0
//already defined at User.h:34
#define DEFAULT_RESPAWN 0
// how does stamina works ?

#define INTERACTION_RANGE 8

// a day
// 1 to 1.5 L drinked through food and still need to drink 1.5 to 2 L of pure water - let's take respectively 1 and 2 - so 3 for the total
// 2.5 kg of food

#define DAY_DRINK_THROUGH_FOOD_SI 1.0
#define DAY_IN_GAME_TIME_SECONDS 3600.0
//#define DAY_IN_GAME_TIME_SECONDS 400.0
#define DAY_FOOD_KG 2.5
#define DAY_DRINK_L 3.0

#define HEAD_HEIGHT 1.35
#define HEAD_SIZE 0.45

extern double defaultX, defaultY, defaultZ, defaultPhi, defaultTheta;

/// TODO: should use unsigned long long everywhere we use unsigned int for money

class User
{
    public:
        User(), User(std::string/* = "User_Default"*/, View = View(Position(defaultX, defaultY, defaultZ), ViewAngle(defaultPhi, defaultTheta)), std::string = "-1.-1.-1.-1", unsigned short = 0, unsigned short = 0, bool isFake = false);
        void initializeTexture(), updateView(View, bool = false), updateView(Vector2D), save(), setLanguage(std::string), setFlying(bool, bool = false, bool dontSend = false), setLastConnection(unsigned long long), setTime(unsigned long long),
             setTimeCredit(unsigned long long), setConnected(bool), setAdminLevel(unsigned short, bool = false), setPoliceLevel(unsigned short, bool = false), setVIPLevel(unsigned short, bool = false), setJob(unsigned short, bool = false),
             setBAC(bool, bool = false), setTokens(unsigned int), addTokens(unsigned int), setShop(bool), switchSocialSpying(), setSocialSpying(bool), setLicense(unsigned short, bool, bool = false),
             setLicenses(bool*, unsigned short, bool = false), setMoney(unsigned long long = DEFAULT_MONEY, bool = false), addMoney(unsigned long long, bool needSync = true), setMoneyATM(unsigned long long, bool = false),
             addMoneyATM(unsigned long long, bool needSync = true), setFood(unsigned short = DEFAULT_FOOD, bool = false), addFood(short), setDrink(unsigned short = DEFAULT_DRINK, bool = false), addDrink(short),
             setHealth(unsigned short = DEFAULT_HEALTH, bool = false, bool force = false), removeHealth(unsigned short), setRegen(unsigned short = DEFAULT_REGEN, bool = false), setBleeding(unsigned short = DEFAULT_BLEEDING, bool = false),
             setBreakBone(unsigned short = DEFAULT_BREAK_BONE, bool = false), setGang(std::string, bool = false), setKeys(std::vector<unsigned int>, bool = false), setInterpol(std::vector<std::string>), setSpeed(double, bool = false),
             setGod(bool, bool = false), switchGod(), kill(bool force = false), setVanished(bool, bool = false), switchVanished(), setCuffed(bool = DEFAULT_CUFFED, bool = false), setEscorted(std::string = DEFAULT_ESCORTED, bool = false),
             setEscorting(std::string = DEFAULT_ESCORTING, bool = false), setIP(std::string), setPort(std::string), clear(), setDisconnection(unsigned int), incrementDisconnection(), setStamina(double = DEFAULT_STAMINA, bool = false),
             setInventory(std::string, bool = false), addRespawn(), setRespawn(unsigned int, bool = false), healthConsumption(double timePassed), addHealth(short/*not unsigned !*/), addKey(unsigned int),
             setRidingVehicleId(unsigned int vehicleId = UNSIGNED_INT_MAX), removeMoneyDouble(double), clearLicenses(), setLoading(std::string load = ""), performLoading(), clearHands(), connectEvent(), move(unsigned long long livingForMs),
             computeOBB(View = View()), clearBackpack(), setPositionState(std::string = DEFAULT_ANIMATION, bool sendToEveryone = false), removeKey(unsigned int, bool trustMeDontTrustQuantumCode = false), setInventoryStr(std::string = "");
        View getView(), getViewDeath();
        View* getViewPtr();
	std::string getIP(), getUsername(), getLanguage(), getEscorted(), getEscorting(), getFile(), getPositionState(), getInventoryStr();
        unsigned short getUserId(), getPort(), getAdminLevel(), getPoliceLevel(), getVIPLevel(), getJob(), getHealth();
        unsigned int getTokens(), getDisconnection(), getRespawn(), getRidingVehicleId();
        bool isFlying(), isConnected(), isBAC(), isShop(), isSocialSpying(), isGod(), isVanished(), removeTokens(unsigned int), removeMoney(unsigned long long, bool needSync = true), removeMoneyATM(unsigned long long, bool needSync = true),
             isCuffed(), isSegmentPenetrating(Vector3D a, Vector3D b, User* debugUser = nullptr), isRidingVehicle(), isDriver(), hasKey(unsigned int), hasLicense(unsigned short), isDead(), giveItemUser(unsigned int, unsigned int), isFake(), *getLicenses();
        unsigned long long getLastConnection(), getTime(), getTimeCredit(), getMoney(), getMoneyATM();
        double getSpeed(), getStamina(), getHospitalPrice();
        Inventory* getInventoryPtr();
        OBB getOBB();
    private:
        std::string m_username, m_ip, m_portStr, m_language, m_gangName, m_escorted, m_escorting, m_loading/*, m_huntingUsername*/, m_animation, m_inventoryStr; // could use a User pointer for huntingUser ? or circular build lol
        View m_view, m_viewDeath;
        unsigned short m_userId, m_port, m_adminLevel, m_policeLevel, m_vipLevel, m_job, m_food, m_drink, m_health, m_regen, m_bleeding, m_breakBone;
        unsigned int m_tokens, m_disconnection, m_ridingVehicleId;
        bool m_isFlying, m_connected, m_isBAC, m_isShop, m_isSocialSpying, m_licenses[LICENSE_NUMBER], m_isGod, m_isVanished, m_isCuffed, m_isFake;
        unsigned long long m_lastConnection, m_time, m_timeCredit, m_respawn, m_loadingStartTime, m_money, m_moneyATM;
        double m_speed, m_stamina;
        std::vector<unsigned int> m_keys;
        std::vector<std::string> m_interpol;
        void syncFood(unsigned short = UNSIGNED_SHORT_MAX), syncDrink(unsigned short = UNSIGNED_SHORT_MAX), syncHealth(unsigned short = UNSIGNED_SHORT_MAX);
        Inventory m_inventory;
        OBB m_obb; // should be named likewise on client side
};

extern std::map<std::string, User> users;
extern std::string username, usersFolder;
void addUser(std::string), addUser(std::string, View), addUser(std::string, View, std::string),
     addUser(std::string, View, std::string, unsigned short, unsigned short, bool isFake = false), initializeUsers(), setTokens(std::string, unsigned int),
     setTimeCredit(std::string, unsigned long long), addTokens(std::string, unsigned int), setAdminLevel(std::string, unsigned short),
     setPoliceLevel(std::string, unsigned short), setVIPLevel(std::string, unsigned short), setJob(std::string, unsigned short), setBAC(std::string, bool),
     setHealth(std::string, unsigned short = DEFAULT_HEALTH), setFood(std::string, unsigned short = DEFAULT_FOOD), setFlying(std::string, bool = DEFAULT_FLY),
     setRegen(std::string, unsigned short = DEFAULT_REGEN), setBreakBone(std::string, unsigned short = DEFAULT_BREAK_BONE), setDrink(std::string, unsigned short = DEFAULT_DRINK),
     switchGod(std::string), kill(std::string, bool force = false), setLicense(std::string, unsigned short, bool), switchVanished(std::string),
     setMoney(std::string, unsigned long long), addMoney(std::string, unsigned long long), setMoneyATM(std::string, unsigned long long),
     addMoneyATM(std::string, unsigned long long), switchFly(std::string), clear(std::string), setSpeed(std::string, double = DEFAULT_SPEED), clearLicenses(std::string),
     initializeLoadings(), removeWallet(View, unsigned int itemOnGroundIndex), addWallet(View, unsigned long long walletMoney), clearHands(std::string),
     addFakeUser(std::string, View), makeUsersLive(), removeUser(std::string username), loadStructuresShadow(), manageZombieSpawn(), clearBackpack(std::string clearingUsername),
     eraseUser(std::string), saveUsers();
User* getUser(std::string), *getUserIgnoreCase(std::string), /*getUser(std::string, std::string),*//*why ambiguous ? doesn't matter because isn't used*/ *getUserByIPAndPort(std::string, unsigned short), *getUserByIPAndPort(std::string, std::string);
bool isNicknameCorrect(std::string), isBAC(std::string), isUserExisting(std::string), isUserExistingWithoutConsideringCase(std::string), isGod(std::string), isAdminGrade(std::string), isPoliceGrade(std::string), isVIPGrade(std::string), isJob(std::string), isLicense(std::string), isLicense(unsigned short), isVanished(std::string), removeTokens(std::string, unsigned int), removeMoney(std::string, unsigned long long), removeMoneyATM(std::string, unsigned int), isFlying(std::string), isConnected(std::string, bool isInGame = false), isConnected(User*), giveItemUser(std::string, unsigned int, unsigned short);
unsigned int getTokens(std::string), getWalletSize();
unsigned short getAdminLevelFromGrade(std::string), getPoliceLevelFromGrade(std::string), getVIPLevelFromGrade(std::string), getJobFromGrade(std::string), getLicenseId(std::string), getAdminLevel(std::string), getPoliceLevel(std::string), getJob(std::string), getVIPLevel(std::string);
std::string getAdminGrade(unsigned short), getLicenseString(unsigned short), itemsInHandsToString(), backpacksToString(std::string withoutUsername = ""),
            getFile(std::string username), allWalletsToString(), walletsToString(), allFlyingToString(), formatUsername(std::string), getVIPGrade(unsigned short value),
            getJobGrade(unsigned short value), getPoliceGrade(unsigned short value), getIP(std::string savedUsername);
unsigned long long getTimeCredit(std::string), getWallet(View);
double getSpeed(std::string);
std::vector<View> getWalletViews();
std::vector<std::string> getSavedUsernames();

#endif

// adminLevel:
// 0 Civilian
// 1 Helper
// 2 Moderator
// 3 Administrator
// 4 Developer
// 5 Fondateur
// 6 Host (Benjamin Loison)

// policeLevel:
// 0 Civilian
// 1 Adjoint
// 2 Brigadier
// 3 Sergent
// 4 Adjudant
// 5 Major
// 6 Aspirant
// 7 Lieutenant
// 8 Capitaine
// 9 Colonell
// 10 GÃ©nÃ©ral

// vipLevel:
// 0 Civilian
// 1 VIP
// 2 VIP+
// 3 Chouquette fourÃ©e
// 4 Baguette tradition
// 5 Baguette premium
