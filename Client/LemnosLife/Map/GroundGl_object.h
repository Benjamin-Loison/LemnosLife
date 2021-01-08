#ifndef DEF_GROUND_GL_OBJECT
#define DEF_GROUND_GL_OBJECT

#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/gl.h>
#include <string>
#include <vector>
#include <glm.hpp>
#include "../Render/Shader.h"
#include "StructureMeta.h"

class GroundGl_object
{
    public:
        GroundGl_object();
        GroundGl_object(std::string, bool = true);
        void addPart(double[4][2], std::string[4][3], bool isRoad = false),
             addPart(double[4][2], double[4][3], bool isRoad = false),
             addPart(double[4][2], std::vector<double>, bool isRoad = false),
             deleteParts(),
             initializeTexture(std::string additionnalOption = "", bool force = false),
             initializeRender(bool callInitializeTexture = true, bool forceInitializeTexture = false),
             updateRender(),
             render(bool isRoad = false),
             changeBoolFirst(bool);
        std::string m_texturePath;

        /// following public just for saving this data as binary file
        std::vector<glm::vec4> m_vertices;
        std::vector<glm::vec2> m_texCoord;
        std::vector<unsigned int> m_indices;
        int m_partNumber;
    private:
        GLuint m_texture;
        bool m_first;
        Shader m_shader0;
        unsigned int m_VBO, m_VAO, m_IBO;
        int m_vertice, m_tex, m_indice;
};

#endif
