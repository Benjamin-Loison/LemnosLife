#ifndef DEF_CHUNK
#define DEF_CHUNK

/// should precise FILE in macro's name ?
#define OBJECTS_EXTENSION ".objects"
#define GROUND_EXTENSION ".heights"
#include <string>
#include <vector>
#include <map>
#include "../Structure.h"
#include "../MapGlObject.h"

class Chunk
{
public:
    Chunk();
    Chunk(std::string, std::vector<std::string>);
    void render(), initializeRender(), initializeTransitions(), initGround();
    std::vector<glm::vec3> getTranslations(unsigned int), getRotations(unsigned int);
    std::vector<glm::vec3>* getTranslationsPtr(unsigned int), *getRotationsPtr(unsigned int);
    int getX(), getY();
    bool needInit;
    std::map<unsigned int, Structure> m_structures;

    /*template <class Archive>
    void serialize(Archive& ar)
    {
        ar(X, Y);
    }*/
private:
    std::string m_chunkName;
    std::vector<MapGlObject> m_ground;
    bool m_isLoading;
};

void initializeChunk(), getInCoordinates(glm::vec3*);
std::map<std::string, Chunk> loadFile(std::string, bool = false);
std::string getChunkName(double[2]), getChunkName(double, double), getChunkName(Vector3D, bool withZ = false), getChunk1kName(double[2]), getChunk1kName(double, double), getChunk1kName(Vector3D), getChunk1kName(glm::vec3), getChunkObjectName(double[2]),
    getChunkObjectName(double x, double y), getChunkObjectName(Vector3D), getInCoordinatesStr(double x);
std::pair<unsigned short, unsigned short> getChunk1k(std::pair<double, double> xy);
double getInCoordinates(double x);
extern std::string objectsFolder, groundFolder;

#endif
