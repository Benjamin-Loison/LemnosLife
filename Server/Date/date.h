#ifndef DATE_H_INCLUDED
#define DATE_H_INCLUDED

#include <string>

#define TEN_MINUTES_IN_SECONDS 600
#define HOUR_IN_SECONDS 3600
#define DAY_IN_SECONDS 86400
#define WEEK_IN_SECONDS 604800
#define FOUR_WEEKS_IN_SECONDS 2419200

std::string getDate(bool = /*false*/true), getTimeStr(std::string, std::string, std::string, unsigned int, std::string);
long long getMillis();
unsigned long long getSeconds();

#endif