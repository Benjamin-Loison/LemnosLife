#ifndef DEF_GUICHAT
#define DEF_GUICHAT

#include "Gui.h"
#include <string>

class GuiChat : public Gui
{
    public:
        void initGui(), resizeGui(), renderGui(), freeGui();
};

extern std::vector<std::string> messageList;
extern std::string writingText;

#endif
