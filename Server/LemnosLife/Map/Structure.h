#ifndef DEF_STRUCTURE
#define DEF_STRUCTURE

#define STRUCTURE_FILE_EXTENSION ".struc"
#include "Gl_object.h"

#include <cereal/archives/binary.hpp>
#include <cereal/types/vector.hpp>
//#include <cereal/access.hpp>

class Structure
{
    public:
        Structure(), Structure(std::string);
        void initializeTranslations(), initializeTranslations(std::vector<Vector3D>, std::vector<Vector3D>), addMeta(Vector3D, Vector3D), addMeta(double x, double y, double z, unsigned short rot);
        std::vector<Vector3D> getTranslations(), getRotations();
        std::vector<Vector3D>* getTranslationsPtr(), *getRotationsPtr();
        Gl_object m_glObject;

    //private:
        std::vector<Vector3D> m_structuresMetaTrans, m_structuresMetaRot;

        //friend class cereal::access;

        template <class Archive>
        void serialize(Archive& ar)
        {
            ar(m_structuresMetaTrans, m_structuresMetaRot, m_glObject);
        }
};

Gl_object loadFileStruc(std::string);

#endif