#ifndef DEF_DYNAMIC_GL_OBJECT
#define DEF_DYNAMIC_GL_OBJECT

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
#include "User/View.h"
//#include "User/Inventory.h"

// why not in Vehicle.h ?
//#define VEHICLES_SAVE

class DynamicGl_object
{
public:
    DynamicGl_object();
    DynamicGl_object(std::vector<std::string>, bool = true);
    void addPart(double[4][2], std::string[4][3], unsigned short textureIndex = 0),
         addPart(double[4][2], double[4][3], unsigned short textureIndex = 0),
         deleteParts(),
         initializeTexture(bool force = false),
         initializeRender(),
         initializeTranslations(std::vector<glm::vec3>, std::vector<glm::vec3>, bool updating = false),
         initializeTranslations(std::vector<glm::vec3>*, std::vector<glm::vec3>*, bool updating = false),
         initializeTranslations(std::map<unsigned int, glm::vec3>, std::map<unsigned int, glm::vec3>),
         updateTranslations(std::vector<glm::vec3>, std::vector<glm::vec3>),
         render(bool isHelicopter = false),
         changeBoolFirst(bool),
         initialize(bool updating = false), /// <- useless comment: "///"
         deleteFromId(unsigned int),  // not gpu one
         deleteFromGPUId(unsigned int),
         addWithId(unsigned int id, glm::vec3, glm::vec3), // realId
         modify(unsigned int id, glm::vec3, glm::vec3),
         clear(bool force = false, unsigned int itemId = 0/*DEFAULT_ITEM*/, bool debug = false),
         deleteFromView(View view);
    std::string debugString();
    std::vector<std::string> m_texturePaths;
    std::vector<glm::vec4> m_vertices; // how can it compiles if here vec3 and in cpp vec4 ?!
    unsigned int add(glm::vec3 coo = glm::vec3(), glm::vec3 rot = glm::vec3()); // default arguments are for testing purpose (at least coo)
    std::map<unsigned int, glm::vec3> m_translations, m_rotations; // <gpuId, data>

    std::vector<GLuint> m_textures; // for cerealizing in DynamicGl_Object and next two too
    std::vector<glm::vec2> m_texCoord;
    std::vector<unsigned int> m_indices;
#ifdef VEHICLES_SAVE
    std::vector<std::string> m_texturesVehicleSave;
#endif

    int m_vertice, m_tex, m_indice, m_partNumber; // why not unsigned ? - used like before but only with set and not get way
    unsigned int m_size;

    /*template <class Archive>
    void serialize(Archive& ar)
    {
        ar(m_texturePaths, m_transparency, m_textures, m_partNumber, m_realSize, m_maxId, m_vertices, m_texCoord, m_indices, m_partNumber);
    }*/
private:
    std::map<unsigned int, unsigned int> idToGPUId;
    bool m_sky, m_transparency, m_first;
    Shader m_shaderSpecific, m_shaderMultipleTexturesDiscardAboveFifth;
    unsigned int m_VBO, m_VAO, m_translationVBO, m_angleVBO, m_IBO, m_realSize, m_maxId;
    glm::mat4 modelview; // what's this doing here, it's more general, right?
};

bool isOneNull(std::vector<GLuint>*);
DynamicGl_object getDynamicGl_object(std::string texture, bool download = true);
extern glm::vec3 currentRotation, currentPosition;

#endif
