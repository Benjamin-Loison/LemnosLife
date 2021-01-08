#ifndef SDLGLUTILS_H
#define SDLGLUTILS_H

#include <GL/gl.h>
#include <SDL2/SDL.h>
#include <string>
#include <vector>

GLuint loadSkinTexture(const char*),
       loadTexture(const char*, bool = false, bool isRoad = false, bool isMap = false, bool reverse = false),
       loadTextureNearest(const char*),
       loadSky(std::vector<std::string> filename),
       loadText(std::string, std::string, int),
       loadSVG(const char*, std::string = "");
SDL_Surface *flipSurface(SDL_Surface*);
bool takeScreenshot(std::string filename, unsigned short technology = 0);

//#define TEST_TIME_WITHOUT_FLIP
// doesn't save time at least around 1 ms, yes I said a single ms

#endif
