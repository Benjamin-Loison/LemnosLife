#ifndef DEF_MAP_GL_OBJECT
#define DEF_MAP_GL_OBJECT

#define GLEW_STATIC
#include <GL/glew.h>
#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../Render/Shader.h"

class MapGlObject
{
public:
    MapGlObject();
    MapGlObject(std::string, double[4][2], double[4][3], bool = false, bool = true);
    MapGlObject(std::string, double[4][2], std::string[4][3], bool = false, bool = true);
    void initializeTexture(), initializeRender(), render(glm::vec3 translation = glm::vec3(0, 0, 0));
private:
    double m_tex[4][2], m_vertex[4][3];
    int m_vertices, m_size;
    std::string m_texturePath;
    GLuint m_texture;
    bool m_sky;
    Shader shader;
    unsigned int m_VBO, m_VAO;
};

#endif
