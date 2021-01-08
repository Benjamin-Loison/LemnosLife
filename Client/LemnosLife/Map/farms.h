#ifndef DEF_FARMS
#define DEF_FARMS

#include <map>
#include <string>
#include <vector>

void initializeFarms();
bool isInAFarm(point);

extern std::map<std::string, std::vector<point>> farms;
point getBarycenter(std::vector<point>);

#endif
