#ifndef DEF_ANIMATION
#define DEF_ANIMATION

#include "../LemnosLife/Map/User/User.h"

#define DEFAULT_ANIMATION "standing"

void initializeAnimations(), setStatic(User* user, std::string staticName), setDynamic(User* user, std::string dynamicName), setStaticNotGraphicThread(User* user, std::string staticName),
     setStaticNotGraphicThread(std::string username, std::string staticName), manageAnimations(), loadAnimation(std::string);
extern unsigned int transSize;
bool isAnAnimationName(std::string animationName), isAStaticAnimationName(std::string animationName), isADynamicAnimationName(std::string animationName);
std::vector<std::tuple<std::string, glm::vec3, glm::vec3>> getCurrentAnimation(User* user, std::string positionName);

unsigned short indexForBodyPart(std::string positionName, std::string bodyPart);
extern std::map<std::string, std::vector<std::tuple<std::string, glm::vec3, glm::vec3>>> animations;
glm::vec3 getGLMVec3(std::string str, bool needComputation = false, bool toRadians = false, std::string delimiter = ";");

#endif
