#ifndef DEF_OBJECTS
#define DEF_OBJECTS

#include <tuple>
#include <vector>

#include "../../Collisions/Vector3D.h"

std::tuple<unsigned short, short, double, unsigned short, Vector3D, std::vector<Vector3D>, std::string> getStructureIdTargetingPos(Vector3D origin, Vector3D target);
extern std::vector<short> linkStrucVec;
extern std::vector<Structure> strucIdDbStruc;
Vector3D rotationAndTranslation(Vector3D vec, Vector3D middle, double angle);

void loadStructures(), loadObjects();

std::string uploadObjects(std::string mapName, std::string chunk, std::string filePath);

#endif