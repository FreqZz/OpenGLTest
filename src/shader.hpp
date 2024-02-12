#ifndef SHADER_H
#define SHADER_H

#include <initializer_list>

#include <glm/glm.hpp>


class Shader {
public:
    unsigned ID;

    Shader(const char* vShaderPath, const char* fShaderPath);
    ~Shader();

    void use();

    template <typename T>
    void setVec(const char* uniformName, std::initializer_list<T> data);

    template <glm::length_t col, glm::length_t row>
    void setMat(const char* uniformName, const glm::mat<col, row, glm::f32, glm::defaultp>& data);
};

#endif