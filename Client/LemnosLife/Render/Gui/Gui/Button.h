#ifndef BUTTON_H
#define BUTTON_H

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
//#include "Gui.h"

//#define BUTTON_CLICK SDL_USEREVENT

class Button
{
public:
    Button(std::string, std::string, double, double, double, double, /*int, *//*void (*) ()*/bool*, unsigned short = 0, bool = false);
    void resize(double, double, double, double), loadTxt(std::string);
    bool render(SDL_Color color = /*black*/ {0, 0, 0, 255}, bool updateClick = true);
    std::string m_text;
    double m_middleY, m_height;
private:
    std::string m_font;
    double m_middleX, m_width/*, m_code*/;
    GLuint m_textTexture;
    enum state {HOVER, ACTIVE, NOT_HOVER}; // is it the right place to define an enum ?
    Button::state m_state, stateRead();
    unsigned short m_maxChars;
    //SDL_Event events;
    //void (*m_callBack) ();
    bool* m_click, m_reversed; /// should add a destructor to manage this variable at the end of use of buttons
};

void initializeButtons();

#endif
