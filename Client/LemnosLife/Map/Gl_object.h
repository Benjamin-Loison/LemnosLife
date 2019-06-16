#ifndef DEF_GL_OBJECT
#define DEF_GL_OBJECT

#define GLEW_STATIC
#include <glew.h>
#include <gl.h>
#include <string>
#include <vector>
#include <glm.hpp>
#include "../Render/Shader.h"
#include "StructureMeta.h"

class Gl_object
{
    public:
        Gl_object();
        Gl_object(std::string, bool = true);
        void addPart(double[4][2], std::string[4][3]),
        addPart(double[4][2], double[4][3]),
        deleteParts(),
        initializeTexture(),
        initializeRender(),
        initializeTranslations(std::vector<glm::vec3>),
        updateTranslations(std::vector<glm::vec3>),
        render(),
        changeBoolFirst(bool);
        std::vector<std::vector<glm::vec3>> m_p_tmpQuickLaunchVertices;
        std::string m_texturePath;
    private:
        std::vector<glm::vec3> m_vertices;
        std::vector<glm::vec2> m_texCoord;
        std::vector<unsigned int> m_indices;
        GLuint m_texture;
        bool m_sky, m_transparency, m_first;
        Shader m_shader0, m_shader1;
        unsigned int m_VBO, m_VAO, m_translationVBO, m_rotationVBO, m_IBO;
        int m_vertice, m_tex, m_indice, m_size, m_partNumber;
};

#endif
