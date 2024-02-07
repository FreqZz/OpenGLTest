#include "shader.hpp"

#include <glad/glad.h>

#include <iostream>
#include <string>
#include <fstream>

Shader::Shader(const char* vShaderPath, const char* fShaderPath) {
    int success;
    char infoLog[512];

    // vertex shader
    std::ifstream vShaderFile(vShaderPath, std::ios::in | std::ios::binary | std::ios::ate);
    int vShaderLength = (int)vShaderFile.tellg();
    vShaderFile.seekg(0, std::ios::beg);
    char* vShaderSource = new char[vShaderLength + 1];
    vShaderFile.read(vShaderSource, vShaderLength);
    vShaderSource[vShaderLength] = '\0';

    unsigned vShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vShader, 1, &vShaderSource, NULL);
    glCompileShader(vShader);
    delete[] vShaderSource;

    glGetShaderiv(vShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vShader, sizeof(infoLog), NULL, infoLog);
        std::cout << "Failed to compile vertex shader\n" << infoLog << std::endl;
    }

    // fragment shader
    std::ifstream fShaderFile(fShaderPath, std::ios::in | std::ios::binary | std::ios::ate);
    int fShaderLength = (int)fShaderFile.tellg();
    fShaderFile.seekg(0, std::ios::beg);
    char* fShaderSource = new char[fShaderLength + 1];
    fShaderFile.read(fShaderSource, fShaderLength);
    fShaderSource[fShaderLength] = '\0';

    unsigned fShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fShader, 1, &fShaderSource, NULL);
    glCompileShader(fShader);
    delete[] fShaderSource;

    glGetShaderiv(fShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fShader, sizeof(infoLog), NULL, infoLog);
        std::cout << "Failed to compile fragment shader\n" << infoLog << std::endl;
    }

    // link shader program
    ID = glCreateProgram();
    glAttachShader(ID, vShader);
    glAttachShader(ID, fShader);
    glLinkProgram(ID);

    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(ID, sizeof(infoLog), NULL, infoLog);
        std::cout << "Failed to link shader program\n" << infoLog << std::endl;
    }
    glDeleteShader(vShader);
    glDeleteShader(fShader);
}

Shader::~Shader() {
    glDeleteProgram(ID);
}


void Shader::use() {
    glUseProgram(ID);
}