#ifndef SHADER_H
#define SHADER_H


class Shader {
public:
    unsigned ID;

    Shader(const char* vShaderPath, const char* fShaderPath);
    ~Shader();

    void use();
};

#endif

