#ifndef CLIENT_H_INCLUDED
#define CLIENT_H_INCLUDED

#include <thread>
#define NETWORK_SEPARATOR "#REP#"
#define NETWORK_SIZE_SLICE 800

extern std::thread network, disconnected;
void initializeNetwork(), sendStr(std::string), closeConnection(), freeNetwork(), sendPosition(std::string whereAmICalled/* = ""*/), sendOrientation(std::string whereAmICalled/* = ""*/), sendPositionFct(), autoConnect(), sendStrAsChat(std::string), sendStrChatCommand(std::string),
     sendLocal(std::string fakeRcv);
std::string queryServer(std::string);
extern std::string lastPosition, lastOrientation;
extern bool connected/*, useSessionIDInsteadOfIPDetection*/;
extern unsigned int beginTimeConnecting;

#endif
