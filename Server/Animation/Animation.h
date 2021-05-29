#ifndef DEF_ANIMATION
#define DEF_ANIMATION

#include <map>
//#include <string>

#define DEFAULT_ANIMATION "standing"

void initializeAnimations(), manageAnimations(), loadAnimation(std::string);
bool isAnAnimationName(std::string animationName);

extern std::map<std::string, std::vector<std::tuple<std::string, Vector3D, Vector3D>>> animations;
Vector3D getVec3(std::string str, bool needComputation = false, bool toRadians = false, std::string delimiter = ";");
std::pair<Vector3D, Vector3D> getTransRot(std::string animation, std::string bodyPartWanted);

#endif
