#ifndef TEXT_FIELD_H
#define TEXT_FIELD_H

#define GLEW_STATIC
#include <GL/glew.h>
#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif
#include <SDL2/SDL.h>
#include <string>
#include "Button.h"
#include <vector>

class Textfield // should put getters and setters ?
{
public:
    Textfield(std::string, std::string, double, double, double, double, bool = true, unsigned short = 256, bool = false);
    void resize(double, double, double, double), render(), resetTime(), setText(std::string text);
    std::string m_text;
    bool m_typing, buttonClicked = false, m_editable;
    unsigned short m_maxLength;
    unsigned long long initTime;
private:
    void onButtonClicked();
    std::string m_font, m_lastDisplayed;
    double m_middleX, m_middleY, m_width, m_height;
    GLuint m_textTexture;
    enum state {HOVER, ACTIVE, NOT_HOVER, CLICK_ELSEWHERE};
    Textfield::state m_state, stateRead();
    bool m_password, m_show, m_click, m_needReload;
    std::vector<Button> m_buttons;
};

#endif
