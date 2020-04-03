#ifndef DEF_USER
#define DEF_USER

#define GLEW_STATIC
#include <glew.h>
#include <string>
#include <map>
#include "gl.h"
#include "View.h"
#include "../../../3D/Collision/partitioning.h"
#include "../../Render/Shader.h"
#include "ViewGravity.h"
#include "Inventory.h"

#define MAX_HEALTH 100
#define MAX_FOOD 100
#define MAX_DRINK 100
#define MAX_BLEEDING 100
#define MAX_BREAK_BONE 206

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

#define CIVILIAN_JOB 0
// set rebel job when buying license or switch all to license or to job or keep both ?
#define REBEL_JOB 1
// callable (phone)
#define DOCTOR_JOB 2
// callable
#define REPAIRMAN_JOB 3
// callable
#define JOURNALIST_JOB 4
// callable
#define TAXI_JOB 5
#define JOB_NUMBER 6

#define CIVILIAN_VIP 0
#define VIP_VIP 1
#define VIPP_VIP 2
#define CHOUQUETTE_FOURREE_VIP 3
#define BAGUETTE_PREMIUM_VIP 4
#define BAGUETTE_TRADITION_VIP 5
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

#define DEFAULT_SPEED 2.7
#define INTERACTION_RANGE 8
#define DEFAULT_STAMINA 100

#include <thread>

class User
{
    public:
        User(std::string, ViewGravity = ViewGravity(), std::string = "", std::string = ""), User();
        void initializeTexture(bool = false), initializeTextureThread(), initializeRender(), updateViewGravity(ViewGravity, bool = false, bool = false), initUser(), updateOBB(), renderOBB(), changeOBB(OBB), computeOBB(), setAdminLevel(unsigned short),
             setPoliceLevel(unsigned short), setVIPLevel(unsigned short), setJob(unsigned short), setBAC(bool), setSpeed(double), setFood(unsigned short = DEFAULT_FOOD), setDrink(unsigned short = DEFAULT_DRINK), setHealth(unsigned short = DEFAULT_HEALTH),
             setRegen(unsigned short = DEFAULT_REGEN), setBleeding(unsigned short = DEFAULT_BLEEDING), setBreakBone(unsigned short = DEFAULT_BREAK_BONE), setMoney(unsigned int), setMoneyATM(unsigned int), kill(), setLicenses(std::string),
             setLicense(unsigned short, bool), setGang(std::string), setKeys(std::string), setGod(bool), setVanished(bool), setCuffed(bool), setEscorted(std::string), setEscorting(std::string), setStamina(double), leftClick(), stopLeftClicking(), zoom(), unzoom(), renderInventory();
        OBB getOBB();
        const void render();
        ViewGravity* getViewGravity();
        unsigned short getHealth(), getRegen(), getFood(), getDrink(), getBleeding(), getBreakBone(), getAdminLevel(), getPoliceLevel(), getVIPLevel(), getJob();
        std::string getUsername(), getSkin(), m_skin, getEscorting(); // should a getter instead of direct access to variable m_skin
        std::vector<std::string> getLicensesStringVector(), getLicensesNotOwnedStringVector();
        bool isPlayerInTarget(std::string, double = 99999), isNPC(), m_needRefresh = false, m_refreshOBB = false, isBAC(), isVanished(), hasLicense(unsigned short), getLicenses(), m_licenses[LICENSE_NUMBER], isCuffed(), isEscorted(), isEscorting(); // getLicenses() to test/remove
        double getGroundAltitudeDeeperFoot(double, double), getGroundAltitudeDeeperFoot(), getSpeed(), getStamina();
        unsigned int getMoney(), getMoneyATM();
        Inventory* getInventoryPtr();
        GLuint m_texture;
    private:
        std::string m_username, m_action, m_gangName, m_escorted, m_escorting;
        ViewGravity m_viewGravity, m_lastViewGravity;
        int m_height;
        unsigned short m_health, m_regen, m_food, m_drink, m_bleeding, m_breakBone, m_adminLevel, m_policeLevel, m_vipLevel, m_job;
        OBB box;
        Shader shader, shaderObb, shaderObb2;
        unsigned int m_VBO, m_VAO, m_ObbVBO, m_ObbVAO, m_ObbVAO2, m_money, m_moneyATM;
        double m_speed, m_stamina;
        bool m_isCreative, ObbVBOCreated, m_refreshSkinFinished = true, m_isBAC, m_isGod, m_isVanished, m_isCuffed;
        std::thread refreshSkin;
        std::vector<unsigned int> m_keys;
        Inventory m_inventory;
};

extern std::map<std::string, User> users;
extern std::vector<std::string> npcs;
void addUser(std::string), addUser(std::string, ViewGravity), /*addNPC(unsigned int, std::string, ViewGravity, std::string)*/addNPC(std::string, std::string, ViewGravity, std::string), removeUser(std::string), changeBoolOBB();
bool existsPlayer(std::string), isPartNameCorrect(std::string);
const void renderUsers();
User* getUser(std::string), *getTargetingUser();
extern User* thePlayer;
const double eyeHeight = 1.55;
 // SPAWN {8244, 15578, 3.8} // MIDDLE ALTIS {16000, 16000, 100} // BUG {6000, 6000, 100} // ALTIS KAVALA {3500, 13000, 100} // market: 3645.98,13113,10.2444,356.4,-12
std::string getAdminString(unsigned short), getPoliceString(unsigned short);

#endif
