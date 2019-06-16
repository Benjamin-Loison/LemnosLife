#ifndef TEXTUREMANAGER_H_INCLUDED
#define TEXTUREMANAGER_H_INCLUDED

#include <map>
#include <string>
#include <gl.h>

void initializeTextureManager(), freeTextureManager(), addTexture(std::string, std::string);
GLuint addGetTexture(std::string, std::string), getTexture(std::string);
bool isLoaded(std::string);

#endif
