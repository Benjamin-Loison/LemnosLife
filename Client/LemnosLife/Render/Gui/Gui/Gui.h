#ifndef DEF_GUI
#define DEF_GUI

#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/gl.h>
#include <string>
#include <SDL2/SDL_ttf.h>
#include <glm.hpp>
#ifdef _WIN32
    #include <windows.h>
    #include <wingdi.h>
#endif
#include <map>
#include "Radio.h"
#include "TextBox.h"
#include "../../../../2D/vector2d.h"

#define FONT_FILE_EXTENSION ".ttf"

class Gui
{
    public:
        virtual void renderGui(), initGui(), freeGui(), resizeGui();
        virtual bool isDynamic();
    protected:
        void renderGuiInGame();
};

extern Gui* guiScreenPtr, *guiInGamePtr;//, guiStructures, *guiStructuresPtr;
extern SDL_Color white, whiteTransparent, grey, lightGrey, darkGreyTransparent, greyTransparent, lightGreen, blue, black, red, redTransparent, green, darkGreenTransparent, orangeTransparent, lightBlue, beige, darkBeige, yellow, invisible;
extern bool needInit, isResizeGuiReady, guiInGameNeedInit, needResize;
extern std::string currentGui, currentGuiInGame, picturesGuiGuiFolder;
extern std::map<std::string, GLuint> pictures;
extern std::map<std::string, std::pair<double, double>> picturesSizes;
extern std::map<std::string, std::string> guiInputFilters;
extern std::map<std::string, TTF_Font*> fonts;

void glBasics(),
     renderGuiScreen(),

     setGuiScreen(std::string),
     setGuiInGame(std::string, bool isShop = false, bool isVehicle = false, bool isPlayer = false),

     switchGuiInGame(std::string, bool = false),
     initGui(),
     prepare2D(),
     setColor(SDL_Color),
     realResizeGui(),
     resizeGui(),
     initializeGui(),
     freeGui(),

     displayColor(double, double, double, double, SDL_Color = white),
     displayColor(double, double, double, double, double, double, double, double, SDL_Color = white),
     displayColor(std::vector<Vector2D> vec, SDL_Color color),
     displayColor(Vector2D vec, SDL_Color color, double size = 2),

     displayLine(double x0, double y0, double x1, double y1, SDL_Color color, double z0 = 0, double z1 = 0, unsigned short width = 1),

     displayLine(std::vector<Vector2D> vec, SDL_Color color, double z0 = 0, double z1 = 0, unsigned short width = 1),

     displayPicture(GLuint, double, double, double, double, std::string = "", double = 0, float picMinX = 0, float picMinY = 0, float picMaxX = 1, float picMaxY = 1, bool needTransparency = false),
     displayPicture(std::string, double, double, double, double, bool = false, double = 0, float picMinX = 0, float picMinY = 0, float picMaxX = 1, float picMaxY = 1),
     displayPicture(std::vector<Vector2D> coordinates, std::string pictureId),

     displayTextRegularRight(std::string, double, double, double, double, std::string, SDL_Color, bool, unsigned short),
     displayTextRegularLeft(std::string, double, double, double, double, std::string, SDL_Color, bool, unsigned short, unsigned short = 1),
     displayTextRegular(std::string, double, double, double, double, std::string, SDL_Color, bool, unsigned short),
     displayTextRegular(GLuint, double, double, double, double, std::string, SDL_Color, unsigned short, unsigned short, bool),

     displayText(std::string, double, double, double, double, std::string = "arial", SDL_Color = white, bool = false, double = 1, SDL_Color = invisible),
     displayText(unsigned char, double, double, double, double, std::string = "arial", SDL_Color = white),
     displayText(GLuint, double, double, double, double, SDL_Color = white, bool = false), // this parameter doesn't make sens here , bool displayOnce = false

     enableMouse(),
     disableMouse(),
     initializePictureGui(std::string, std::string, std::string);

glm::vec4 getGLMColor(SDL_Color color);

#include "GuiLogin.h"
#include "GuiMouseOver.h"
#include "GuiLemnosInventory.h"
#include "GuiOptions.h"
#include "GuiMap.h"

extern GuiLogin* guiLoginPtr;
extern GuiMouseOver* guiMouseOverPtr;
extern GuiLemnosInventory* guiLemnosInventoryPtr;
extern GuiOptions* guiOptionsPtr;
extern GuiMap* guiMapPtr;

GLuint initializeGLText(SDL_Surface* flippedSurface);

// can't use this, love bugs <3
//#include "GuiInventory.h"
//extern GuiInventory* guiInventoryPtr;

unsigned long long getAmount(std::string);

#endif
