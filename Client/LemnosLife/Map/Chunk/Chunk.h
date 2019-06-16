#ifndef DEF_CHUNK 
#define DEF_CHUNK

#define OBJECTS_EXTENSION ".objects"
#define GROUND_EXTENSION ".height"
#include <string> 
#include <vector> 
#include <map> 
#include "../StructureMeta.h" 
#include "../Structure.h"
#include "../MapGlObject.h"

class Chunk 
{ 
    public: 
        Chunk(); 
        Chunk(std::string, std::vector<std::string>); 
        void render(), initializeRender(), initializeTransitions(), initGround();
        std::vector<glm::vec3> getTranslations(int);
        int getX(), getY(); 
        bool needInit; 
    private: 
        std::string m_chunkName; 
        std::map<int, Structure> m_structures;
        std::vector<MapGlObject> m_ground;
        bool m_isLoading; 
}; 

void initializeChunk();
std::map<std::string, Chunk> loadFile(std::string);
std::string getChunkName(double[2]), getChunk1kName(double[2]);
extern std::string objectsFolder, groundFolder;

#endif