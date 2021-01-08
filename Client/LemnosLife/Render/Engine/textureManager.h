#ifndef TEXTUREMANAGER_H_INCLUDED
#define TEXTUREMANAGER_H_INCLUDED

#include <map>
#include <string>
#include <GL/gl.h>

void initializeTextureManager(), freeTextureManager();
GLuint addGetTexture(std::string, std::string, bool = false), getTexture(std::string);
bool isLoaded(std::string), addTexture(std::string, std::string, std::string = ""), finishedLoadingEverything();
extern std::map<std::string, GLuint> textures; // optimization purpose (not very OOP like)

#endif
