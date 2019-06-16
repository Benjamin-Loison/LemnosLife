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

#define MAX_HEALTH 100
#define MAX_FOOD 100
#define MAX_DRINK 100
#define MAX_BLEEDING 100
#define MAX_BREAK_BONE 206

#define MAX_HEALTH_DIGIT_NUMBER 3
#define MAX_FOOD_DIGIT_NUMBER 3
#define MAX_DRINK_DIGIT_NUMBER 3
#define MAX_BLEEDING_DIGIT_NUMBER 3
#define MAX_BREAK_BONE_DIGIT_NUMBER 3

class User
{
    public:
        User(std::string, ViewGravity = ViewGravity()), User();
        void initializeTexture(), initializeRender(), updateViewGravity(ViewGravity, bool = false), initUser(), updateOBB(), renderOBB(), changeOBB(OBB), computeOBB();
        OBB getOBB();
        const void render();
        ViewGravity* getViewGravity();
        unsigned short getHealth(), getRegen(), getFood(), getDrink(), getBleeding(), getBreakBone();
        std::string getUsername();
        bool isPlayerInTarget(std::string);
        double getGroundAltitudeDeeperFoot(double, double), getGroundAltitudeDeeperFoot();
    private:
        std::string m_username;
        ViewGravity m_viewGravity, m_lastViewGravity;
        GLuint m_texture;
        int m_height;
        unsigned short m_health, m_regen, m_food, m_drink, m_bleeding, m_break_bone;
        OBB box;
        Shader shader, shaderObb, shaderObb2;
        unsigned int m_VBO, m_VAO, m_ObbVBO, m_ObbVAO, m_ObbVAO2;
        bool m_isCreative, ObbVBOCreated;
};

extern std::map<std::string, User> users;
void addUser(std::string), addUser(std::string, ViewGravity), removeUser(std::string);
bool existsPlayer(std::string);
const void renderUsers();
User* getUser(std::string);
const double eyeHeight = 1.55, defaultSpawn[3] = {15500, 15500, 100}; // SPAWN {8244, 15578, 3.8} // MIDDLE ALTIS {16000, 16000, 100} // BUG {6000, 6000, 100} // ALTIS KAVALA {3500, 13000, 100}
void changeBoolOBB();

#endif
