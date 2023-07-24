#ifndef DEF_ROAD_GL_OBJECT
#define DEF_ROAD_GL_OBJECT

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
#include "../Render/Shader.h"

///#define DEBUG_ROADS

class RoadGl_object
{
public:
    RoadGl_object();
    RoadGl_object(std::string, bool = true);
    void addPart(double[4][2], double[4][3]),
         deleteParts(),
         initializeTexture(std::string additionalOption = "", bool force = false),
         initializeRender(bool callInitializeTexture = true, bool forceInitializeTexture = false),
         updateRender(),
         render(bool currentGLDebug = 0),
         changeBoolFirst(bool);
    std::string m_texturePath;

    /// following public just for saving this data as binary file
    std::vector<glm::vec3> m_vertices;
    std::vector<glm::vec2> m_texCoord;
    std::vector<unsigned int> m_indices;
    int m_partNumber;
private:
    GLuint m_texture;
    bool m_first, m_textureLoadedOnce;
    Shader m_shader;
    unsigned int m_VBO, m_VAO, m_IBO;
    int m_vertice, m_tex, m_indice;
};

extern unsigned long long roadTotalIndices;

#endif
