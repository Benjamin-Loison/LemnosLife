#ifndef TICK_BOX_H
#define TICK_BOX_H

// are all these includes really necessary ?
#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <string>

class TickBox
{
    public:
        TickBox(bool, std::string, double, double, double, double);
        void resize(double, double, double, double), loadTxt(std::string), render();
        std::string m_text;
        double m_middleY, m_height;
    private:
        std::string m_font;
        double m_middleX, m_width;
        GLuint m_textTexture, m_textureNotHover, m_textureHover, m_textureActive;
        enum state{HOVER, ACTIVE, NOT_HOVER};
        TickBox::state m_state, stateRead();
};

#endif
