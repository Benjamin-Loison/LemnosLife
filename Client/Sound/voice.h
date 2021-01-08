#ifndef VOICE_H_INCLUDED
#define VOICE_H_INCLUDED

// 30 Mo
/*#define BUFFER_SIZE 30000000
#define DESIRED_FREQ 44100
#define DESIRED_SAMPLES 4096
#define DESIRED_FORMAT AUDIO_U8*/

#include <string>

void initializeVoice(), startVocal(), stopVocal(), freeVocal();
bool isVocalOn();

extern std::string voiceFolder, voiceSendFolder, voiceUtilitiesFolder, voiceReceivedFolder;

#endif
