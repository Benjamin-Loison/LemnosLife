#ifndef LOGGER_H_INCLUDED
#define LOGGER_H_INCLUDED

#include <string>
#include <map>
#include <vector>
#include <tuple>

void initializeLogger(), print(std::string), print(int), debug(std::string), archive(std::string), exitWithMessage(std::string), print(std::tuple<std::map<std::string, bool>, std::map<std::string, double>, std::map<std::string, long long>, std::map<std::string, std::string>>), print(std::map<std::string, std::string>), freeLogger();

#endif