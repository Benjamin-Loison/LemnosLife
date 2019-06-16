#ifndef DEF_STRUCTURE  
#define DEF_STRUCTURE  

#define GLEW_STATIC 
#include <glew.h> 
#include <gl.h> 
#include <glext.h> 
#include <glm.hpp> 
#include <gtx/transform.hpp> 
#include <gtc/type_ptr.hpp> 
#include <vector>  
#include <string>
#include <utility>
#include <map>
#include "Gl_object.h"  
#include "StructureMeta.h"  

class Structure  
{  
    public:  
        Structure(), Structure(std::string);  
        void initializeRender(), initializeTranslations(), initializeTranslations(std::vector<glm::vec3>), updateTranslations(std::vector<glm::vec3>), render(), addMeta(glm::vec3);
        std::vector<glm::vec3> getTranslations();
    private:  
        Gl_object m_glObject;
        std::map<int, std::vector<double>> rotations;
        std::vector<glm::vec3> m_structuresMeta;  
};  

Gl_object loadFileStruc(std::string, bool sky = false);  

#endif