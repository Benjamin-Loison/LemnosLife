#ifndef SHADER_H
#define SHADER_H

#define GLEW_STATIC
#include <glew.h>
#include <gl.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "Engine/engine.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
    public:
        unsigned int ID;
        Shader(const char* vertexPath, const char* fragmentPath);
        Shader(std::string);
        Shader();
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
         void checkCompileErrors(unsigned int shader, std::string type);
		 std::string m_vertexPath, m_fragmentPath;
};

#endif
