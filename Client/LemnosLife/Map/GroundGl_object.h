#ifndef DEF_GROUND_GL_OBJECT
#define DEF_GROUND_GL_OBJECT

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

class GroundGl_object
{
public:
    GroundGl_object();
    GroundGl_object(std::vector<std::string>, bool = true);
    void addPart(float, unsigned int, std::pair<unsigned int, unsigned int>),
         deleteParts(),
         initializeTexture(std::string additionalOption = "", bool force = false),
         initializeRender(bool callInitializeTexture = true, bool forceInitializeTexture = false),
         updateRender(),
         render(bool currentGLDebug = 0),
         changeBoolFirst(bool),
         updateVAO();
    std::vector<std::string> m_texturePaths;

    /// following public just for saving this data as binary file
    std::vector<float> m_altitudes;
    std::vector<unsigned int> m_biomes;
    std::vector<glm::uvec2> m_chunks;
    int m_partNumber, m_actualPartNumber;
private:
    std::vector<GLuint> m_textures;
    bool m_first, m_textureLoadedOnce, m_needVAOUpdate;
    Shader m_shader;
    unsigned int m_VBO, m_VAO;
    int m_altitude, m_biome, m_chunk;
};

extern unsigned long long totalIndices;
bool addChatMessageGlError(std::string identifier = ""); // could change these functions location
void addChatMessageSDLError(std::string identifier = "");

#endif
