#ifndef DATE_H_INCLUDED
#define DATE_H_INCLUDED

#include <string>

// getNbZero should be string_plus
std::string getDate(), getDate(unsigned int timeSeconds), getNbZero(double, unsigned short = 2, bool = false), getHoursMinutesSeconds(unsigned long long timestamp, std::string hourMinuteSeparator = ":", std::string minuteSecondSeparator = ":");
//unsigned int getSecondsSinceBeginning();
unsigned long long getMillis(), getMillisInGame();
void wait(unsigned int ms);

extern double timeSpeed;
extern long long timeOrigin;

#endif
