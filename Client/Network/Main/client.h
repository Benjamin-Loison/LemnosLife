#ifndef CLIENT_H_INCLUDED
#define CLIENT_H_INCLUDED

#include <thread>
#define NETWORK_SEPARATOR "#REP#"
#define NETWORK_SIZE_SLICE 800

extern std::thread network, disconnected;
void initializeNetwork(), sendStr(std::string), closeConnection(), freeNetwork(), sendPosition(std::string whereAmICalled/* = ""*/), sendOrientation(std::string whereAmICalled/* = ""*/), sendPositionFct(), autoConnect(), sendStrChatCommand(std::string),
     sendLocal(std::string fakeRcv), launchThreadAutoConnect(), processServerAsset(bool mainMenuAfter = false), launchThreadProcessServerAsset(bool mainMenuAfter = false);
std::string queryServer(std::string);
extern std::string lastPosition, lastOrientation;
extern bool connected, waitNetwork/*, useSessionIDInsteadOfIPDetection*//*, readyToReceiveNetworkData*/;
extern unsigned int beginTimeConnecting;

#endif
