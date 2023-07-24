#ifndef DEF_GUICHAT
#define DEF_GUICHAT

#include "Gui.h"
#include <vector>
#include <string>

#define CHAT_MAX_LENGTH 180

class GuiChat : public Gui
{
public:
    void initGui(), resizeGui(), renderGui(), freeGui();
private:
    double m_windowHeightDiv31;
};

extern std::vector<std::string> messageList, messageSentList;
extern std::vector<double> timeList;
extern std::string writingText, lastMessage;
extern unsigned int messageIndex;
void addChatMessage(std::string), previousMessage(), nextMessage(), addChatMessageOnce(std::string), clearChat(), addChatMessageIfDifferentFromPreviousOne(std::string);

#endif
