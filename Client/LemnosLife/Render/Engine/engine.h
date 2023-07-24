#ifndef ENGINE_H_INCLUDED
#define ENGINE_H_INCLUDED

#include "../Gui/Gui/Gui.h"
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../../../3D/Render/Engine/freeflycamera.h"

#ifdef WIN32
#define JPG ".jpg"
#define PNG ".png"
#define SVG ".svg"
#define BMP ".bmp"
#else
#define JPG ".jpg"
#define PNG ".png"
#define SVG ".svg"
#define BMP ".bmp"
#endif

extern Gui* guiScreen;
extern bool mipmap, potentialFps, engineInit, isFullscreen, screenshotAsked, graphicCardIsAMD, graphicCardIsIntel;//, needResizeGui;
extern double fov, zNear, zFar, resizeWidth, resizeHeight, pixelLike, windowWidth, windowWidthDiv2, windowWidthDiv4, windowWidthDiv5, windowWidthDiv8, windowWidthDiv10, windowWidthDiv11, windowWidthDiv20, windowWidthDiv25, windowWidthDiv30, windowWidthDiv40, windowWidthDiv50, windowWidthDiv60, windowWidthDiv80, windowWidthDiv100, windowWidthDiv200, windowWidthDiv400, windowWidthDiv500,
       windowHeight, windowHeightDiv2, windowHeightDiv4, windowHeightDiv6, windowHeightDiv8, windowHeightDiv10, windowHeightDiv20, windowHeightDiv25, windowHeightDiv30, windowHeightDiv35, windowHeightDiv40, windowHeightDiv50, windowHeightDiv60, windowHeightDiv75, windowHeightDiv80, windowHeightDiv100, windowHeightDiv200, windowHeightDiv400, windowHeightDiv500,
       windowHeightDiv1000, windowInitialWidth, windowInitialHeight, patch, ratioX, ratioY;
void initializeEngine(), launchGame(), renderScreen(int), refreshScreen(), size(), freeEngine(bool skipWaiting = false), initGraphics(), changeModelview(glm::mat4), changeFov(double = 70, double zNear = -1, double zFar = -1, bool force = false), writeMipMapFile();
//extern unsigned int zfar;
extern unsigned short fps;
extern std::string lastRealFPS;
extern SDL_Surface* text;
extern FreeFlyCamera* camera;
extern SDL_Window* screen;
//extern SDL_Renderer* renderer;
extern SDL_GLContext mainGlContext, textureManagerGlContext, changeChunkGlContext;
extern FreeFlyCamera* camera;
extern std::string realFPSStr, shadersFolder, graphicCard;
glm::mat4 getProjection(), getModelview();
std::string getResolution();
extern std::vector<std::string> mipMapDisabled;
extern long long currentTimeDebug;
extern std::thread::id graphicalThreadId;

bool isGraphicThread();

#endif
