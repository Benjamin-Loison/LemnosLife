#ifndef SDLGLUTILS_H
#define SDLGLUTILS_H
 
#include <gl.h>
#include <SDL.h>
#include <string>
#include <vector>
 
GLuint loadSkinTexture(const char*);
GLuint loadTexture(const char*, bool = false);
GLuint loadTextureNearest(const char*);
GLuint loadSky(std::vector<std::string> filename);
GLuint loadText(std::string, std::string, int);
GLuint loadSVG(const char*);
int takeScreenshot(const char*);
SDL_Surface *flipSurface(SDL_Surface*);
 
#endif