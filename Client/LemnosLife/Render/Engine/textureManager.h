#ifndef TEXTUREMANAGER_H_INCLUDED
#define TEXTUREMANAGER_H_INCLUDED

#include <map>
#include <string>
#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

void initializeTextureManager(), freeTextureManager();
GLuint addGetTexture(std::string, std::string = "", bool = false), getTexture(std::string);
bool isLoaded(std::string), addTexture(std::string, std::string = "", std::string = "", bool force = false), finishedLoadingEverything();
extern std::map<std::string, GLuint> textures; // optimization purpose (not very OOP like)

#endif
