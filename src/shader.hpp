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
    template <glm::length_t L>
    void setVec(const char* uniformName, const glm::vec<L, float, glm::defaultp>& data);

    template <glm::length_t C, glm::length_t R>
    void setMat(const char* uniformName, const glm::mat<C, R, glm::f32, glm::defaultp>& data);
};

#endif