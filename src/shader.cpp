#include "shader.hpp"

#include <glad/glad.h>

#include <iostream>
#include <string>
#include <fstream>
#include <initializer_list>
#include <type_traits>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

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

template <typename T>
void Shader::setVec(const char* uniformName, std::initializer_list<T> data) {
    if constexpr (std::is_same<T, int>::value) {
        switch (data.size()) {
            case 1:
                glUniform1iv(glGetUniformLocation(ID, uniformName), 1, data.begin());
                break;
            case 2:
                glUniform2iv(glGetUniformLocation(ID, uniformName), 1, data.begin());
                break;
            case 3:
                glUniform3iv(glGetUniformLocation(ID, uniformName), 1, data.begin());
                break;
            case 4:
                glUniform4iv(glGetUniformLocation(ID, uniformName), 1, data.begin());
                break;
            default:
                std::cout << "Invalid amount of inputs for uniform." << std::endl;
        }
    }
    else if constexpr (std::is_same<T, float>::value) {
        switch (data.size()) {
            case 1:
                glUniform1fv(glGetUniformLocation(ID, uniformName), 1, data.begin());
                break;
            case 2:
                glUniform2fv(glGetUniformLocation(ID, uniformName), 1, data.begin());
                break;
            case 3:
                glUniform3fv(glGetUniformLocation(ID, uniformName), 1, data.begin());
                break;
            case 4:
                glUniform4fv(glGetUniformLocation(ID, uniformName), 1, data.begin());
                break;
            default:
                std::cout << "Invalid amount of inputs for uniform." << std::endl;
        }
    }
}

template <glm::length_t col, glm::length_t row>
void Shader::setMat(const char* uniformName, const glm::mat<col, row, glm::f32, glm::defaultp>& data)
{
    switch (col) {
        case 2:
            switch (row) {
                case 2:
                    glUniformMatrix2fv(glGetUniformLocation(ID, uniformName), 1, GL_FALSE, glm::value_ptr(data));
                    break;
                case 3:
                    glUniformMatrix2x3fv(glGetUniformLocation(ID, uniformName), 1, GL_FALSE, glm::value_ptr(data));
                    break;
                case 4:
                    glUniformMatrix2x4fv(glGetUniformLocation(ID, uniformName), 1, GL_FALSE, glm::value_ptr(data));
                    break;
                default:
                    break;
            }
        case 3:
            switch (row) {
                case 2:
                    glUniformMatrix3x2fv(glGetUniformLocation(ID, uniformName), 1, GL_FALSE, glm::value_ptr(data));
                    break;
                case 3:
                    glUniformMatrix3fv(glGetUniformLocation(ID, uniformName), 1, GL_FALSE, glm::value_ptr(data));
                    break;
                case 4:
                    glUniformMatrix3x4fv(glGetUniformLocation(ID, uniformName), 1, GL_FALSE, glm::value_ptr(data));
                    break;
                default:
                    break;
            }
        case 4:
            switch (row) {
                case 2:
                    glUniformMatrix4x2fv(glGetUniformLocation(ID, uniformName), 1, GL_FALSE, glm::value_ptr(data));
                    break;
                case 3:
                    glUniformMatrix4x3fv(glGetUniformLocation(ID, uniformName), 1, GL_FALSE, glm::value_ptr(data));
                    break;
                case 4:
                    glUniformMatrix4fv(glGetUniformLocation(ID, uniformName), 1, GL_FALSE, glm::value_ptr(data));
                    break;
                default:
                    break;
            }
        default:
            break;
    }
}
template void Shader::setVec(const char* uniformName, std::initializer_list<int> data);
template void Shader::setVec(const char* uniformName, std::initializer_list<float> data);
template void Shader::setMat(const char* uniformName, const glm::mat<4, 4, glm::f32, glm::defaultp>& data);
