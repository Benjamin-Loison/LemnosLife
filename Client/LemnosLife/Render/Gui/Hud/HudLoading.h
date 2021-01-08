#ifndef DEF_HUD_LOADING
#define DEF_HUD_LOADING

#include "../Gui/Gui.h"
#include "../../../Map/User/User.h"

class HudLoading : public Gui
{
    public:
        void renderGui(), resizeGui();
        bool isDynamic();
    private:
        /*std::string message;
        unsigned long long startTime = 0, time;
        bool noLoading = true;*/
        double m_minX, m_maxX, m_minY, m_maxY/*, spaceX, spaceY*/, m_centerY;
};

bool addLoading(unsigned long long ms, std::string msg, /*callbackFunction*/void(*action)(unsigned int)); // compilation interminable sur un problème qui n'a pas de sens, minable g++, 080820 3:48 AM
//bool noLoading = true; /// for at least two hours headache because no error shown with ld return 1, just need toi* use extern ... remove unsigned int above makes the same problem so don't care
extern bool noLoading;
void removeLoading();

#endif
