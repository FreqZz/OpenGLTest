#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>


#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT 600

#define VERTEX_SHADER_PATH ".\\Shaders\\vertexShader.glsl"
#define FRAGMENT_SHADER_PATH ".\\Shaders\\fragmentShader.glsl"


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
// try SDL
void processInput(GLFWwindow* window);




int main() {
    std::cout << "Hello OpenGL!" << std::endl;

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif


    // create GLFW window
    // ------------------
    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "OpenGLTest", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // load GLAD
    // ---------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }


    // build and compile shaders
    // -------------------------
    int success;
    char infoLog[512];

    // vertex shader
    std::ifstream vertexShaderFile(VERTEX_SHADER_PATH, std::ios::in | std::ios::binary | std::ios::ate);
    int vertexShaderLength = (int)vertexShaderFile.tellg();
    vertexShaderFile.seekg(0, std::ios::beg);
    char* vertexShaderSource = new char[vertexShaderLength + 1];
    vertexShaderFile.read(vertexShaderSource, vertexShaderLength);
    vertexShaderSource[vertexShaderLength] = '\0';

    unsigned vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    delete[] vertexShaderSource;

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, sizeof(infoLog), NULL, infoLog);
        std::cout << "Failed to compile vertex shader\n" << infoLog << std::endl;
    }

    //fragment shader
    std::ifstream fragmentShaderFile(FRAGMENT_SHADER_PATH, std::ios::in | std::ios::binary | std::ios::ate);
    int fragmentShaderLength = (int)fragmentShaderFile.tellg();
    fragmentShaderFile.seekg(0, std::ios::beg);
    char* fragmentShaderSource = new char[fragmentShaderLength + 1];
    fragmentShaderFile.read(fragmentShaderSource, fragmentShaderLength);
    fragmentShaderSource[fragmentShaderLength] = '\0';

    unsigned fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    delete[] fragmentShaderSource;

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, sizeof(infoLog), NULL, infoLog);
        std::cout << "Failed to compile fragment shader\n" << infoLog << std::endl;
    }

    // link shaders
    unsigned shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, sizeof(infoLog), NULL, infoLog);
        std::cout << "Failed to link shader program\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    

    // set up vertex data, buffer(s), and configure vertex attributes
    // --------------------------------------------------------------
    float vertices[] = {
         0.5f,  0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f
    };
    unsigned indices[] = {
        0, 1, 2,
        0, 2, 3
    };

    unsigned VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);


    // render loop
    // -----------
    while (!glfwWindowShouldClose(window)) {
        // input
        processInput(window);

        // clear the colorbuffer
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);

        // update uniform
        float blueValue = sin(glfwGetTime()) / 2.0f + 0.5f;
        int vertexColorLocation = glGetUniformLocation(shaderProgram, "myColor");
        glUniform4f(vertexColorLocation, 0.0f, 0.0f, blueValue, 1.0f);

        // render
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // swap the buffers and call events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    // de-allocate all resources
    // -------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);

    glfwTerminate();
    return 0;
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}