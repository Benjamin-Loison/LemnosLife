#ifndef DEF_GL_OBJECT
#define DEF_GL_OBJECT

// Gl_object, Structure and Chunk are copied from client

#include "../../Collisions/Vector3D.h"
#include "../../Collisions/Vector2D.h"

#include <cereal/archives/binary.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/string.hpp>

//#include <cereal/access.hpp>

class Gl_object
{
    public:
        Gl_object();
        Gl_object(std::vector<std::string>);
        void addPart(double[4][2], std::string[4][3], unsigned short textureIndex = 0),
            addPart(double[4][2], double[4][3], unsigned short textureIndex = 0),
            initializeTranslations(std::vector<Vector3D>, std::vector<Vector3D>);
        std::vector<std::string> m_texturePaths;
        std::vector<Vector3D> m_vertices;
        std::vector<bool> m_bulletPartThrough, m_bulletTextureThrough;
        std::vector<unsigned short> m_bulletPartIndexThrough;
    //private:
        std::vector<Vector2D> m_texCoord;
        bool m_transparency;
        int m_vertice, m_tex;

        //friend class cereal::access;

        template <class Archive>
        void serialize(Archive& ar)
        {
            ar(m_texCoord, m_transparency, m_vertice, m_tex, m_vertices, m_texturePaths);
        }
};

#endif