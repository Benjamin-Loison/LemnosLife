#ifndef SHADER_H
#define SHADER_H

#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/gl.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "Engine/engine.h"

#include <string>
#include <fstream>
#include <sstream>
//#include <iostream>

#define VERTEX_FILE_EXTENSION ".vs"
#define FRAGMENT_FILE_EXTENSION ".fs"

class Shader
{
    public:
        unsigned int ID;
        Shader();
        Shader(/*const char**/std::string vertexPath, /*const char**/std::string fragmentPath, unsigned short texturesSize = 1);
        //Shader(std::string);
        //Shader(const char* path);
        //Shader(std::string, std::string);
        void use(),
             setBool(const std::string &name, bool value) const,
             setInt(const std::string &name, int value) const,
             setFloat(const std::string &name, float value) const,
             setVec2(const std::string &name, const glm::vec2 &value) const,
             setVec2(const std::string &name, float x, float y) const,
             setVec3(const std::string &name, const glm::vec3 &value) const,
             setVec3(const std::string &name, float x, float y, float z) const,
             setVec4(const std::string &name, const glm::vec4 &value) const,
             setVec4(const std::string &name, float x, float y, float z, float w),
             setMat2(const std::string &name, const glm::mat2 &mat) const,
             setMat3(const std::string &name, const glm::mat3 &mat) const,
             setMat4(const std::string &name, const glm::mat4 &mat) const;
    private:
        // in order to optimize this code executed 1200x on launching - used to have constructors here
        void checkCompileErrors(unsigned int shader, std::string type);
};

Shader getShader(std::string vertexPath, std::string fragmentPath, unsigned short texturesSize = 1);

#endif
