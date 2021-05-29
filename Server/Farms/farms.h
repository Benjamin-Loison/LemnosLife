#ifndef FARMS_H_INCLUDED
#define FARMS_H_INCLUDED

#include <vector>
#include <string>
#include <vector>
#include <map>
// exist or not ? #include <pair>
#include "../LemnosLife/Map/User/User.h"
#include "../Collisions/Vector2D.h"

#define FARM_FILE_EXTENSION ".plg"

void initializeFarms(), farmUser(User*), removeFarm(std::string), addFarm(std::string, std::string, std::vector<std::pair<double, double>>);
std::vector<std::string> farmList();

extern std::map<std::string, std::vector<Vector2D>> farmsPts;

#endif