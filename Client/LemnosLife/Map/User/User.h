#ifndef DEF_USER
#define DEF_USER

#define GLEW_STATIC
#include <GL/glew.h>
#include <string>
#include <map>
#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif
#include "View.h"
#include "../../../3D/Collision/partitioning.h"
#include "../../Render/Shader.h"
#include "ViewGravity.h"
#include "Inventory.h"
#include "../../../MathPlus/math_plus.h"

#define MAX_HEALTH 100
#define MAX_FOOD 100
#define MAX_DRINK 100
#define MAX_BLEEDING 100
#define MAX_BREAK_BONE 206

// not all min are used on client-side

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

#define MAX_HEALTH_DIGIT_NUMBER 3
#define MAX_FOOD_DIGIT_NUMBER 3
#define MAX_DRINK_DIGIT_NUMBER 3
#define MAX_BLEEDING_DIGIT_NUMBER 3
#define MAX_BREAK_BONE_DIGIT_NUMBER 3

#define CIVILIAN_ADM 0
#define HELPER_ADM 1
// should add Architect ?
#define MODERATOR_ADM 2
#define ADMINISTRATOR_ADM 3
#define DEVELOPER_ADM 4
#define FONDATOR_ADM 5
#define HOST_ADM 6
#define ADM_NUMBER 7

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
// set rebel job when buying license or switch all to license or to job or keep both?
#define REBEL_JOB 1
#define DOCTOR_JOB 2
#define REPAIRMAN_JOB 3
#define JOURNALIST_JOB 4
#define TAXI_JOB 5
#define JOB_NUMBER 6
extern std::string jobGrades[JOB_NUMBER];

#define CIVILIAN_VIP 0
#define VIP_VIP 1
#define VIP_VIPP 2
#define CHOUQUETTE_FOURREE_VIP 3
#define BAGUETTE_TRADITION_VIP 4
#define BAGUETTE_PREMIUM_VIP 5
#define VIP_NUMBER 6
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

// need to have same value as server otherwise
#define DEFAULT_SPEED 1
#define INTERACTION_RANGE_3D 5
#define INTERACTION_RANGE_2D 3.5
/// sqrt(2) ratio
/// used to be 8 should make it variable for "creative" like mode ?
#define ITEM_INTERACTION_RANGE 3
#define DEFAULT_STAMINA 100

#define FULL_HEAL_PRICE 100

#define PLAYER_REAL float

#include <thread>

// does god mode make hunger and thirst not active ?

//enum PositionState {SEATING, STANDING, LYING};
//#define PositionState unsigned int
//extern std::map<std::string, unsigned int> positionStates;

class User
{
public:
    User(std::string, ViewGravity = ViewGravity(), std::string = "", std::string = ""), User();
    void initializeTexture(bool = false), initializeTextureThread(), initializeRender(), updateViewGravity(ViewGravity, bool = false, bool = false, bool dontUpdateViewAngle = false, bool dontSned = false), initUser(), updateOBB(), renderOBB(), changeOBB(OBB), computeOBB(Position = Position(), ViewAngle = ViewAngle()), setAdminLevel(unsigned short),
         setPoliceLevel(unsigned short), setVIPLevel(unsigned short), setJob(unsigned short), setBAC(bool), setSpeed(double), setFood(unsigned short = DEFAULT_FOOD), setDrink(unsigned short = DEFAULT_DRINK), setHealth(unsigned short = DEFAULT_HEALTH),
         addHealth(short), setRegen(unsigned short = DEFAULT_REGEN), setBleeding(unsigned short = DEFAULT_BLEEDING), setBreakBone(unsigned short = DEFAULT_BREAK_BONE), addMoney(unsigned long long), removeMoney(unsigned long long), setMoney(unsigned long long), setMoneyATM(unsigned long long), kill(), setLicenses(std::string),
         setLicense(unsigned short, bool), setGang(std::string), setKeys(std::string), setGod(bool), setVanished(bool), setCuffed(bool), setTasered(bool), setEscorted(std::string), setEscorting(std::string), setStamina(double), leftClick(), stopLeftClicking(), zoom(), unzoom(), renderInventory(),
         addMoneyATM(unsigned long long), removeMoneyATM(unsigned long long)/*, setRidingVehicleSeat(Seat*)*//*, can put this code back only if change m_ridingVehicleSeat - can't use Seat* here so doing this way*/, setRidingVehicleId(unsigned int = UNSIGNED_INT_MAX),
         removeMoneyDouble(double), addKey(unsigned int), setNeedHandRender(bool needHandRender = false), setNeedBackRender(bool needHandRender = false), setItemInHandId(unsigned int itemId = UNSIGNED_INT_MAX), setItemInHandRenderId(unsigned int = UNSIGNED_INT_MAX), setItemOnBackId(unsigned int itemId = UNSIGNED_INT_MAX), setItemOnBackRenderId(unsigned int = UNSIGNED_INT_MAX),
         setStuffInHands(bool = false), setStuffOnBack(bool = false), setJustRemovedHand(bool = false), setJustRemovedBack(bool = false),
         needToBeRemoved(), setBodyPart(std::string bodyPart, double degrees0, double degrees1), setPositionState(/*PositionState*/std::string), removeKey(unsigned int), setFlying(bool isFlying = false),//, setAnimation(std::string);
         switchCuffed();
    OBB getOBB(), *getOBBPtr();
    const void render();
    ViewGravity* getViewGravity();
    unsigned short getHealth(), getRegen(), getFood(), getDrink(), getBleeding(), getBreakBone(), getAdminLevel(), getPoliceLevel(), getVIPLevel(), getJob();
    std::string getUsername(), getSkin(), m_skin, getEscorting(), getAction(), getGangName(), getPositionState(); // should a getter instead of direct access to variable m_skin
    std::vector<std::string> getLicensesStringVector(), getLicensesNotOwnedStringVector();
    std::vector<unsigned int> getKeys();
    bool isPlayerInTarget(/*std::string*/User*, double = 99999)/*could use DBL_MIN or DBL_MAX*/, isCreative(), isNPC(), m_needRefresh = false, m_refreshOBB = false, isBAC(), isVanished(), hasLicense(unsigned short), getLicenses(), m_licenses[LICENSE_NUMBER], isCuffed(), isTasered(), isEscorted(),
         isEscorting(), isRidingVehicle(), isDriver(), hasKey(unsigned int), getNeedHandRender(), getNeedBackRender(), hasStuffInHands(), getStuffOnBack(), getJustRemovedHand(), getJustRemovedBack(), getNeedToBeRemoved(), getOBBVBOCreated(), isFlying(), cantMove(); // getLicenses() to test/remove
    double getGroundAltitudeDeeperFoot(double, double), getGroundAltitudeDeeperFoot(), getSpeed(), getStamina(), getHospitalPrice(), m_eyeHeight;//, getEyeHeight();
    unsigned int getRidingVehicleId(), getItemInHandId(), getItemInHandRenderId(), getItemOnBackId(), getItemOnBackRenderId(), getVBO();
    unsigned long long getMoney(), getMoneyATM(), getPositionStateTimeOrigin();
    Inventory* getInventoryPtr();
    GLuint m_texture;
    //Seat* getRidingVehicleSeat(); // problem can't have two classes which have both a reference to each other
    //PositionState getPositionState();
private:
    std::string m_username, m_action, m_gangName, m_escorted, m_escorting, m_positionState;//, m_currentAnimation;
    ViewGravity m_viewGravity, m_lastViewGravity;
    int m_height;
    unsigned short m_regen, m_food, m_drink, m_bleeding, m_breakBone, m_adminLevel, m_policeLevel, m_vipLevel, m_job;
    short m_health; // if use unsigned short, don't hear hurt sound when loose all life with a single free fall
    OBB box;
    Shader shader, shaderObb, shaderObb2;
    unsigned int m_VBO, m_VAO, m_ObbVBO, m_ObbVAO, m_ObbVAO2, m_ridingVehicleId, m_itemInHandRenderId, m_itemInHandId, m_itemOnBackRenderId, m_itemOnBackId;
    double m_speed, m_stamina;
    bool m_isCreative, ObbVBOCreated, m_refreshSkinFinished = true, m_isBAC, m_isGod, m_isVanished, m_isCuffed, m_isTasered, m_needHandRender, m_needBackRender, m_stuffInHands, m_stuffOnBack, m_justRemovedHand, m_justRemovedBack, m_needToBeRemoved, m_isFlying;
    unsigned long long m_money, m_moneyATM, m_positionStateTimeOrigin;
    std::thread refreshSkin;
    std::vector<unsigned int> m_keys;
    Inventory m_inventory;
    //PositionState m_positionState;
};

//typedef void (*callbackFunction)(void);
// don't mess with unsigned "long long" for great numbers it seems very equivalent to unsigned "long" - ah it's at least and therefore my precision is not guaranteed on other computers, well I wait to see - well need long long finally

//#define getEyeHeight() eyeHeight
// could just rename getEyeHeight() everywhere in code ... - let's do so because compiler seems stupid...

extern std::map<std::pair<double, double>, double> teleportationZ;
extern std::map<View, unsigned long long> wallets;
extern std::map<std::string, User> users;
extern std::vector<std::string> npcs;
std::vector<std::string> getUsersWithoutThePlayer(double maxDistance = 100000);
void addUser(std::string), addUser(std::string, ViewGravity), /*addNPC(unsigned int, std::string, ViewGravity, std::string)*/addNPC(std::string, std::string, ViewGravity, std::string), removeUser(std::string), changeBoolOBB(), resetNPCs(), beHealed(unsigned int = 0), healed(unsigned int),
     addWallet(View, unsigned long long walletMoney), pickWallet(unsigned int itemsOnGroundIndex), removeWallet(View), initializeUsers();
unsigned long long getWallet(View);
bool existsPlayer(std::string), isPartNameCorrect(std::string), findWallet(View);
const void renderUsers();
User* getUser(std::string), *getTargetingUser(), *getUserIgnoreCase(std::string);
extern User* thePlayer; // use real constants with uppercase or want to troll with variables ?
const double /*eyeHeight = 1.55, */user3DHypothenuse = 1.86/*manually computed, exact value: 9 * sqrt(17) / 20, let's overrate it*/; /// could use a perspective with zNear 0.19 to improve quality but this would involve to manage greater distances with walls etc
//extern double eyeHeight;
extern const PLAYER_REAL headHeight, headSize;
#define BODY_HEIGHT (headHeight + headSize)
// SPAWN {8244, 15578, 3.8} // MIDDLE ALTIS {16000, 16000, 100} // BUG {6000, 6000, 100} // ALTIS Myrina {3500, 13000, 100} // market: 3645.98,13113,10.2444,356.4,-12
std::string getAdminString(unsigned short), getPoliceString(unsigned short), walletsToString();
unsigned int getItemOnGround();
extern bool obbDebug, noAmmoRequired;
extern std::map<std::string, unsigned int> partIndexes, partSizes;
extern unsigned long long totalTimeDownloadingSkins, taseredTime;
unsigned short getPoliceIndex(std::string policeGrade);
//extern std::mutex teleportationZLock;
//double getEyeHeight();
//PositionState getPositionState(std::string);
/*#include "../../../Vehicles/Vehicle.h"
double distance(User*, Vehicle*);*/

// funny idea two heads fit on the user body could do it ?

#endif
