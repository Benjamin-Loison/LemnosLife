#ifndef DEF_MAPUTILS
#define DEF_MAPUTILS

#include "Position.h"

double getGroundAltitude(double x, double y), getGroundAltitude(Position); // first function not used as public
void removeStructure(unsigned int structureId, Vector3D pos, unsigned short rot, bool verbose = true), addStructure(std::tuple<unsigned int, Vector3D, Vector3D> tupl, bool verbose = true);

#endif