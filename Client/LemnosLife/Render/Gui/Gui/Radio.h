#ifndef RADIO_H
#define RADIO_H

#include <vector>
#include <string>
#include "Button.h"

class Radio
{
    public:
        Radio(std::vector<std::string>, unsigned short, unsigned short = 41, bool = false, bool = false, bool = false);
        void resize(double, double, double, double, double), render(), init(std::vector<std::string>); // init used to be private
        std::string m_selection;
        std::vector<std::string> m_options, m_changeOptions;
        bool button0Clicked = false, button1Clicked = false, button2Clicked = false, boolTrash;
    private:
        std::vector<Button> m_buttons, m_btns, m_textboxbuttons;
        std::vector<bool> m_show;
        double m_centerX, m_centerY, m_widthDiv2, m_heightDiv2, m_spaceBetweenLines;
        void onButton0Clicked(), onButton1Clicked(), onButton2Clicked(), refresh(), updateButtons()/*, checkAndAmplify(short)*/;
        bool m_expanded = false, m_hideTextAndExpand = false, m_reversed;
        unsigned short m_lines, m_index, m_maxChars;
};

#endif
