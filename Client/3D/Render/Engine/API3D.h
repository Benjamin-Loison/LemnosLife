#ifndef API3D_H
#define API3D_H

#include "../../../LemnosLife/Render/Engine/engine.h"
#include "../../../LemnosLife/Render/Shader.h"
#include <float.h> // why is it here ?
#include "../../Collision/partitioning.h"

#define HEIGHT_LINE_3D 1000

class Line3D // can be coded with one VAO ... ? (if so is better ?)
{
public:
    /// add a destructor to manage GPU variables
    Line3D();
    Line3D(float, float, glm::vec4 = glm::vec4(1, 0, 0, 1), float = -HEIGHT_LINE_3D, float = DBL_MAX, float = 0, float = HEIGHT_LINE_3D);
    Line3D(std::vector<double>, glm::vec4 = glm::vec4(1, 0, 0, 1));
    void render(), free();
    float m_verticesCoo[6];
private:
    glm::vec4 m_color;
    unsigned int m_VBO, m_VAO, m_vertices;
    Shader m_shader; // can be used for multiple instances ?
};

#include "../../../LemnosLife/Map/Position.h"
#include "../../../2D/vector2d.h"
Line3D getLine3D(Point, glm::vec4), getLine3D(Position, glm::vec4 = glm::vec4(1, 0, 0, 1)), getLine3D(Vector2D, glm::vec4 = glm::vec4(1, 0, 0, 1));

#endif
