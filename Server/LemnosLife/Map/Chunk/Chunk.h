#ifndef DEF_CHUNK
#define DEF_CHUNK

#define OBJECTS_EXTENSION ".objects"
#define GROUND_EXTENSION ".height"
#include <string>
#include "../Structure.h"
#include "../objects.h"

#include <cereal/archives/binary.hpp>
#include <cereal/types/map.hpp>
//#include <cereal/access.hpp>

class Chunk
{
    public:
        Chunk();
        Chunk(std::string, std::vector<std::string>);
        void initializeTransitions();
        std::vector<Vector3D> getTranslations(unsigned int), getRotations(unsigned int);
        std::vector<Vector3D>* getTranslationsPtr(unsigned int), *getRotationsPtr(unsigned int);
        int getX(), getY();
        std::map<unsigned int, Structure> m_structures;
        std::string m_chunkName; // just for cereal because the private method as descriebed here: https://uscilab.github.io/cereal/serialization_functions.html doesn't seem to work - how maybe my mistake - indeed (need to serialize by myself my other objects like Structure ^^) - well finally need public x)
    //private:

        //friend class cereal::access;

        template <class Archive>
        void serialize(Archive& ar)
        {
            ar(m_structures, m_chunkName); // doesn't also work with nested in nested objects...
        }
};

std::string getChunk1kName(double[2]), getChunk1kName(double x, double y), getChunk1kName(Vector3D), getChunkName(double x, double y), getChunkName(Vector3D), getInCoordinatesStr(double), getChunkObjectName(Vector3D), getChunkObjectName(double x, double y);
void initializeChunk();

extern std::string groundFolder, objectsFolder;
std::map<std::string, Chunk> loadFile(std::string chunkName);
double getInCoordinates(double);

#endif