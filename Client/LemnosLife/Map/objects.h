#ifndef DEF_OBJECTS
#define DEF_OBJECTS

#include <string>
#include "Structure.h"

#define ID_ATM_NOT_COVERED 280
#define ID_ATM_COVERED 416

#define MAX_STRUCTURE_HYPOTENUSE_3D 48.58
#define MAX_STRUCTURE_HYPOTENUSE_2D 22.85

void loadStructures(), loadObjects(std::string), initObjectsRender(), initObjectRender(unsigned short, bool force = false), renderObjects(), reloadStructures(), reloadStructure(unsigned short), initItemsRender(), initItemsOnGround();

Vector3D rotationAndTranslation(Vector3D, Vector3D, double degrees, bool cleanMethod = false),
         isRectangleInTarget(Vector3D A, Vector3D B, Vector3D C, Vector3D D, bool descendingFromFoot, bool descending, Vector3D from),
         rotationAndTranslation(glm::vec4, Vector3D, double degrees, bool cleanMethod = false);

extern std::vector<short> linkStrucVec;
extern std::vector<Structure> strucIdDbStruc;
extern std::vector<std::string> strucIdDbStr;
extern std::vector<bool> strucIdDbBool;
extern std::map<int, std::vector<glm::vec3>> strucTranslations; // used for debugging

//std::tuple<unsigned short, unsigned short, unsigned short> getStructureIdTargeting(bool = false);
std::tuple<unsigned short, short, /*unsigned short*/double, std::vector<double>, unsigned short, Vector3D> getStructureIdTargeting(bool = false, bool drawRed = true), getStructureIdTargetingPos(bool, double, double, double, bool = false, bool = false, Vector3D = Vector3D(), OBB* = nullptr, bool drawRed = true);

bool isAnATM(unsigned short), lookingAnATM(unsigned short, unsigned short);

double getMaxRadius(std::vector<glm::vec3> vertices), getMaxRadius(std::vector<glm::vec4> vertices);

extern unsigned int itemsOnGroundAlready3D;
extern unsigned long long checked, checkedDescending, checkedDescendingFromFoot, realChecked;

#endif
