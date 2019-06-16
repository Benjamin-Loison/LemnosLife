#ifndef LOGGER_H_INCLUDED
#define LOGGER_H_INCLUDED

#include <map>
#include <tuple>
#include <string>
#include <glm.hpp>

void initializeLogger(), print(std::string), write(std::string), display(std::string), debug(std::string), print(double), print(std::map<std::string, std::string>), print(std::tuple<std::map<std::string, bool>, std::map<std::string, double>, std::map<std::string, long>, std::map<std::string, std::string>>), print(glm::vec3), exitWithMessage(std::string), freeLogger();
extern std::string fatalDev;

//add fct for printing fatalDev and exit/crash-report like exitWithMessage but with more details ?

#endif
