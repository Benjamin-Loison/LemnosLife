#ifndef SOUND_H_INCLUDED
#define SOUND_H_INCLUDED

#include <thread>
#include "../LemnosLife/Map/Position.h"
#include <string>
#include <atomic>

extern std::thread soundThread;
void initializeSound()/*, playSound(std::string, Position = Position()/*, Position = Position()*//*, double = 100), */,
     playSound(std::string, Position = Position(), std::atomic<bool>* = nullptr, Position* = nullptr),
     playSounde(std::string, Position, std::atomic<bool>*, Position* = nullptr), downloadAndPlay(std::string url, std::string filePath), freeSound();

extern std::string soundsFolder;
extern double PITCH;
extern unsigned int FREQUENCY;
extern short FORMAT;
extern bool soundTime, seeVocalChat;

#endif
