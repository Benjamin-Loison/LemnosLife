#ifndef LOGGER_H_INCLUDED
#define LOGGER_H_INCLUDED

#include <map>
#include <tuple>
#include <string>
#include <glm/glm.hpp>
#include <vector>

void initializeLogger(), occasionnal(std::string), print(std::string = ""), write(std::string), display(std::string), debug(std::string), print(double), print(std::map<std::string, std::string>), print(std::tuple<std::map<std::string, bool>, std::map<std::string, double>, std::map<std::string, long long>, std::map<std::string, std::string>>), print(glm::vec3), exitWithMessage(std::string), displayError(), beginThread(std::string), endThread(std::string, unsigned short), freeLogger();
extern std::string fatalDev, logPath;
extern bool logIntoVector;
extern std::vector<std::string> vectorLogs;

//add fct for printing fatalDev and exit/crash-report like exitWithMessage but with more details ?

#endif
