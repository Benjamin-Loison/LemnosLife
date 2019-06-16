#ifndef BUTTON_H
#define BUTTON_H

#define GLEW_STATIC
#include <glew.h>
#include <gl.h>
#include <glu.h>
#include <SDL.h>
#include <string>

#define BOUTON_CLIQUE SDL_USEREVENT

class Button
{
    public:
        Button(std::string, std::string, int, int, int, int, int);
        void resize(int, int, int, int), render();
    private:
        std::string m_text, m_font;
        int m_middleX, m_middleY, m_width, m_height, m_code;
        GLuint m_textTexture, m_textureNotHover, m_textureHover, m_textureActive;
        enum etat{HOVER, ACTIVE, NOT_HOVER};
        Button::etat m_state;
        Button::etat stateRead();
        SDL_Event evenements;
};

#endif // BUTTON_H
