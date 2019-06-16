#ifndef API3D_H
#define API3D_H

#include "../../../LemnosLife/Render/Engine/engine.h"
#include "../../../LemnosLife/Render/Shader.h"

class Line3D // can be coded with one VAO ... ? (if so is better ?)
{
    public:
        Line3D();
        Line3D(double, double, glm::vec4 = glm::vec4(1, 0, 0, 1));
        Line3D(std::vector<double>, glm::vec4 = glm::vec4(1, 0, 0, 1));
        void render();
    private:
        glm::vec4 m_color;
        unsigned int m_VBO, m_VAO, m_vertices;
        Shader m_shader; // can be used for multiple instances ?
};

#endif