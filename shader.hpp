#ifndef SHADER_H
#define SHADER_H

#include <initializer_list>


class Shader {
public:
    unsigned ID;

    Shader(const char* vShaderPath, const char* fShaderPath);
    ~Shader();

    void use();

    void uniformInt(const char* uniformName, std::initializer_list<int> valueList);
    void uniformFloat(const char* uniformName, std::initializer_list<float> valueList);
};

#endif