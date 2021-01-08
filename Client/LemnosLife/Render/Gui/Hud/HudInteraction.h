#ifndef DEF_HUD_INTERACTION
#define DEF_HUD_INTERACTION

#include "../Gui/Gui.h"

// auto dismiss the menu like Arma after a few seconds ?

class HudInteraction : public Gui
{
    public:
        void renderGui(), resizeGui(), scrollDown(), scrollUp(), select(), addOption(std::string, void (*)(unsigned int), unsigned int = 0), removeOption(std::string);
        bool isDynamic(), isEmpty(), needScrollDown = false, needScrollUp = false;
    private:
        unsigned int getOptionIndex(std::string);
        void addOptionIfNotIn(std::string, void (*)(unsigned int), unsigned int), removeOptionsBeginningBy(std::string translated);
};

void loadStructuresDoors();

#endif
