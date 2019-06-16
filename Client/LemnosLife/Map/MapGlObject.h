#ifndef DEF_MAP_GL_OBJECT
#define DEF_MAP_GL_OBJECT

#define GLEW_STATIC
#include <glew.h>
#include <gl.h>
#include <string>
#include <vector>
#include <glm.hpp>
#include <gtx/transform.hpp>
#include <gtc/type_ptr.hpp>
#include "../Render/Shader.h"
#include "StructureMeta.h"

class MapGlObject
{
    public:
        MapGlObject();
        MapGlObject(int, std::string, std::string, double[4][2], double[4][3], bool = false, bool = true);
        MapGlObject(int, std::string, std::string, double[4][2], std::string[4][3], bool = false, bool = true);
        void initializeTexture(), initializeRender(), render(glm::vec3 translation = glm::vec3(0, 0, 0));
    private:
        double m_tex[4][2], m_vertex[4][3];
        int m_id;
        std::string m_type, m_texturePath;
        GLuint m_texture;
        bool m_sky;
        Shader shader;
        unsigned int m_VBO, m_VAO;
        int m_vertices;
        int m_size;
};

#endif
