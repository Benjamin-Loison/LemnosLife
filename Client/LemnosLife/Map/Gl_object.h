#ifndef DEF_GL_OBJECT
#define DEF_GL_OBJECT

#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/gl.h>
#include <string>
#include <vector>
#include <glm.hpp>
#include "../Render/Shader.h"
#include "StructureMeta.h"

class Gl_object
{
    public:
        Gl_object();
        Gl_object(std::vector<std::string>, bool = true/*, bool firstDebug = false*/);
        //Gl_object(std::string, bool = true);
        void addPart(double[4][2], std::string[4][3], unsigned short textureIndex = 0),
            addPart(double[4][2], double[4][3], unsigned short textureIndex = 0),
            deleteParts(),
            initializeTexture(bool force = false),
            initializeRender(),
            initializeTranslations(std::vector<glm::vec3>, std::vector<glm::vec3>, bool force = false),
            initializeTranslations(std::vector<glm::vec3>*, std::vector<glm::vec3>*, bool force = false),
            updateTranslations(std::vector<glm::vec3>, std::vector<glm::vec3>),
            render(/*bool renderDebug = false*/);
            //changeBoolFirst(bool);
            //removeTranslationRotation(glm::vec3 trans, glm::vec3 rot),
            //removeTranslationRotation(Vector3D trans, unsigned short rot);
        //std::vector<std::vector<glm::vec3>> m_p_tmpQuickLaunchVertices;
        std::vector<glm::vec4>* getVerticesPtr();
        std::vector<std::string> m_texturePaths;
        std::vector<glm::vec4> m_vertices;
    private:
        std::vector<glm::vec2> m_texCoord;
        //std::vector<int> m_texsIndexes;
        std::vector<unsigned int> m_indices;
        //std::vector<glm::vec3> m_translations, m_rotations; /// don't used to be saved ! - because are saved in structure file
        std::vector<GLuint> m_textures;
        bool m_sky, m_transparency, m_first;//, m_firstDebug, m_needTextureInit;
        Shader m_shader0, m_shader1;
        unsigned int m_VBO, m_VAO, m_translationVBO, m_angleVBO, m_IBO;
        int m_vertice, m_tex, m_indice, m_size, m_partNumber; /// can use unsigned here ?
};

Gl_object getGl_object(std::string texture, bool download = true);

#endif
