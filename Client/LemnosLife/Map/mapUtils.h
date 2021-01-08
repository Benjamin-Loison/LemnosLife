#ifndef DEF_MAPUTILS
#define DEF_MAPUTILS

#include <string>
#include "User/ViewGravity.h"

void groundAltitudeRefresh(), getGroundAltitude(View*), addStructure(std::tuple<unsigned int, glm::vec3, glm::vec3>, bool verbose = true, bool sendToServer = true), removeStructure(unsigned int structureId, Vector3D pos, unsigned short rot, bool verbose = true, bool sendToServer = true),
     removeStructure(std::tuple<unsigned int, Vector3D, unsigned short/* rot*//*lol that was just a try*/>, bool verbose = false, bool sendToServer = true);

double getGroundAltitude(bool = false), getGroundAltitude(double, double, bool = false), getGroundAltitudeWithStructure(), getGroundAltitudeWithStructure(double, double, double), getLongitude(double), getLatitude(double), getGroundAltitude(ViewGravity*),
       getGroundAltitude(Position), getGroundAltitudeWithStructure(Position);
std::string getLongitudeLatitude(double, double, unsigned short = 4, std::string = " "), getLongitudeLatitude(unsigned short = 4, std::string = " ");

#endif
