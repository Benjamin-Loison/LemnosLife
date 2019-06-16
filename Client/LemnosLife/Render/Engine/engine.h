#ifndef ENGINE_H_INCLUDED
#define ENGINE_H_INCLUDED

#include "../Gui/Gui/Gui.h"
#include <glm.hpp>
#include <gtx/transform.hpp>
#include <gtc/type_ptr.hpp>
#include "../../../3D/Render/Engine/freeflycamera.h"

extern Gui *guiScreen;
extern bool mipmap, potentialFps, engineInit;
extern double resizeWidth, resizeHeight, windowWidth, windowWidthDiv2, windowHeight, windowHeightDiv2, windowInitialWidth, windowInitialHeight, patch;
void initializeEngine(), launchGame(), glProjection(), renderScreen(int), refreshScreen(), size(), freeEngine(), initGraphics();
extern unsigned int zfar;
extern unsigned short fps;
extern SDL_Surface *text;
extern FreeFlyCamera *camera;
extern SDL_Window *screen;
extern SDL_GLContext ctx, ctxa;
extern FreeFlyCamera *camera;
extern std::string realFPSStr, shadersFolder;
glm::mat4 getProjection(), getModelview();
void changeProjection(glm::mat4), changeModelview(glm::mat4);
double getWindowWidthDiv2(), getWindowHeightDiv2();

#endif