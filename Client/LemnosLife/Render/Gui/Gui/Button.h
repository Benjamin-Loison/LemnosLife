#ifndef BUTTON_H
#define BUTTON_H

#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL2/SDL.h>
#include <string>

//#define BOUTON_CLIQUE SDL_USEREVENT

class Button
{
    public:
        Button(std::string, std::string, double, double, double, double, /*int, *//*void (*) ()*/bool*, unsigned short = 0, bool = false);
        void resize(double, double, double, double), loadTxt(std::string);
        bool render();
        std::string m_text;
        double m_middleY, m_height;
    private:
        std::string m_font;
        double m_middleX, m_width/*, m_code*/;
        GLuint m_textTexture;
        enum state{HOVER, ACTIVE, NOT_HOVER}; // is it the right place to define an enum ?
        Button::state m_state, stateRead();
        unsigned short m_maxChars;
        //SDL_Event events;
        //void (*m_callBack) ();
        bool* m_click, m_reversed;
};

void initializeButtons();

#endif
