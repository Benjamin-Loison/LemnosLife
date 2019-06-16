#ifndef TEXT_FIELD_H
#define TEXT_FIELD_H

#include <SDL.h>
#include <string>

class Textfield
{
    public:
        Textfield(int, int, int, int, std::string, SDL_Color);
        void init(), render(), free();
    private:
        int m_middleX, m_middleY, m_width, m_height;
        std::string m_font, m_text;
        SDL_Color m_backgroundColor;
};

#endif