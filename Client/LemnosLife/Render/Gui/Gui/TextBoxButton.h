#ifndef TEXTBOXBUTTON_H
#define TEXTBOXBUTTON_H

#include <vector>
#include <string>
#include "Button.h"

class TextBoxButton
{
    public:
        TextBoxButton(unsigned short, unsigned short);
        void resize(double, double, double, double, double), render();
        std::vector<std::string> m_lines, m_linesToDisplay;
        bool button0Clicked = false, button1Clicked = false;
    private:
        double m_centerX, m_centerY, m_spaceBetweenLines, m_widthDiv2, m_heightDiv2;
        unsigned short m_maxChars, m_maxLines, m_index;
        std::vector<Button> m_buttons;
        void onButton0Clicked(), onButton1Clicked(), refresh();
};

#endif
