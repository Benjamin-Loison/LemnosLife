#ifndef DEF_HUD_CHAT
#define DEF_HUD_CHAT

#include "../Gui/Gui.h"
#define HUD_CHAT_DISPLAY_TIME 10000
#define HUD_CHAT_FADE_TIME 5000

class HudChat : public Gui
{
public:
    void renderGui(), resizeGui();
    bool isDynamic();
    double distanceXFromWindowEdge, distanceYFromWindowEdge;
    /*private:
        double m_centerX;*/
};

extern bool displayChat;
extern int chatOffset;

#endif
