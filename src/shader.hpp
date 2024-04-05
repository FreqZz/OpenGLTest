#ifndef SHADER_H
#define SHADER_H

#include <initializer_list>

#include <glm/glm.hpp>


class Shader {
public:
    unsigned ID;

    Shader(const char* vShaderPath, const char* fShaderPath);

    void use();

    void setVec(const char* uniformName, std::initializer_list<int> data);
    void setVec(const char* uniformName, std::initializer_list<float> data);
    
    void setVec(const char* uniformName, const glm::vec2& data);
    void setVec(const char* uniformName, const glm::vec3& data);
    void setVec(const char* uniformName, const glm::vec4& data);

    void setMat(const char* uniformName, const glm::mat2x2& data);
    void setMat(const char* uniformName, const glm::mat2x3& data);
    void setMat(const char* uniformName, const glm::mat2x4& data);
    void setMat(const char* uniformName, const glm::mat3x2& data);
    void setMat(const char* uniformName, const glm::mat3x3& data);
    void setMat(const char* uniformName, const glm::mat3x4& data);
    void setMat(const char* uniformName, const glm::mat4x2& data);
    void setMat(const char* uniformName, const glm::mat4x3& data);
    void setMat(const char* uniformName, const glm::mat4x4& data);
};

#endif