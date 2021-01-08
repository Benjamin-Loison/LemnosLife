#ifndef DEF_ANIMATION
#define DEF_ANIMATION

#include "../LemnosLife/Map/User/User.h"

void initializeAnimations(), setStatic(User* user, std::string staticName), setStaticNotGraphicThread(User* user, std::string staticName), manageAnimations(), loadAnimation(std::string);
extern unsigned int transSize;
bool isAnAnimationName(std::string animationName);

extern std::map<std::string, std::vector<std::tuple<std::string, glm::vec3, glm::vec3>>> animations;
glm::vec3 getGLMVec3(std::string str, bool needComputation = false, bool toRadians = false, std::string delimiter = ";");

#endif
