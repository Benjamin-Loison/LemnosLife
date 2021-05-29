#ifndef DEF_STRUCTURE
#define DEF_STRUCTURE

#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/gl.h>
//#include <glext.h>
#include <glm.hpp>
#include <gtx/transform.hpp>
#include <gtc/type_ptr.hpp>
#include <vector>
#include <string>
//#include <utility>
#include <map>
#include "Gl_object.h"
#include "StructureMeta.h"
#include "DynamicGl_object.h"

#define STRUCTURE_FILE_EXTENSION ".struc"

class Structure
{
    public:
        Structure(), Structure(std::string);
        void initializeRender(), initializeTranslations(), initializeTranslations(std::vector<glm::vec3>, std::vector<glm::vec3>, bool force = false), initializeTranslations(std::vector<glm::vec3>*, std::vector<glm::vec3>*, bool force = false),
             updateTranslations(std::vector<glm::vec3>, std::vector<glm::vec3>), updateTranslations(), render(/*bool needDebug = false*/), addMeta(glm::vec3, glm::vec3), addMeta(double x, double y, double z, unsigned short rot), removeMeta(Vector3D metaT, unsigned short metaR),
             removeMeta(glm::vec3 metaT, glm::vec3 metaR, bool deletion = false);
        std::vector<glm::vec3> getTranslations(), getRotations();
        std::vector<glm::vec3>* getTranslationsPtr(), *getRotationsPtr();
        Gl_object m_glObject;
    private:
        std::vector<glm::vec3> m_structuresMetaTrans, m_structuresMetaRot; // may be accessed with pointers in another file even if private ?
};

Gl_object loadFileStruc(std::string, bool sky = false);
DynamicGl_object loadFileStrucDynamic(std::string structureFile, bool sky = false, std::string camouflage = "", bool isMap = false);
bool isATexture(std::string);

// could for palm structure use a kind of skleton in order to curve leaves ? PhotoShop ?

#endif
