#ifndef SOUND_H_INCLUDED
#define SOUND_H_INCLUDED

#include "../LemnosLife/Map/Position.h"
#include <string>
#include <thread>

extern std::thread soundThread;
void initializeSound(), playSound(std::string, Position = Position(), Position = Position(), double = 100), freeSound();

#endif
