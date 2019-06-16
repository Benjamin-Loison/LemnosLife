#ifndef DEF_GUI 
#define DEF_GUI 

#define GLEW_STATIC
#include <glew.h>
#include <gl.h>
#include <string> 
#include <SDL_ttf.h>
#include <windows.h>
#include <wingdi.h>

class Gui 
{ 
    public: 
        static SDL_Color white, grey, lightGrey, blue; 
        virtual void renderGui(), initGui(), freeGui(); 
        virtual bool isDynamic(); 
    protected: 
        void renderGuiInGame(); 
}; 

extern bool needInit, isResizeGuiReady; 
extern std::string actualGui, actualGuiInGame;

void glBasics(),
renderGuiScreen(), 
setGuiScreen(std::string), 
setGuiInGame(std::string), 
initGui(), 
prepare2D(), 
setColor(SDL_Color), 
resizeGui(), 
initializeGui(), 
freeGui(), 
displayColor(double, double, double, double, SDL_Color = {255, 255, 255, 255}), 
displayPicture(GLuint, double, double, double, double),
displayPicture(std::string, double, double, double, double),
displayText(std::string, double, double, double, double, std::string = "arial", SDL_Color = {255, 255, 255, 255}, bool = false),
displayTextRegularRight(std::string, double, double, double, double, std::string, SDL_Color, bool, unsigned short),
displayTextRegularLeft(std::string, double, double, double, double, std::string, SDL_Color, bool, unsigned short),
displayText(unsigned char, double, double, double, double, std::string = "arial", SDL_Color = {255, 255, 255, 255}),
displayText(GLuint, double, double, double, double, SDL_Color = {255, 255, 255, 255});

#endif 