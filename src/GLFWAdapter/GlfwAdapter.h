#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Shader.h"

#ifndef COMP371_GLFWADAPTER_H
#define COMP371_GLFWADAPTER_H


class GlfwAdapter {
public:
    GlfwAdapter();
    bool init();
    void run(Shader* shader, float vertices[], unsigned int indices[], int verticesSize, int indicesSize);

private:
    const int OPENGL_VERSION = 3;
    const int WINDOW_WIDTH = 800;
    const int WINDOW_HEIGHT = 600;
    const char* WINDOW_NAME = "Assignment 1";
    GLFWwindow* window;
    unsigned int VBO, VAO, EBO;

    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    void processInput();
    void setupVertex(float vertices[], unsigned int indices[], int verticesSize, int indicesSize);
};


#endif //COMP371_GLFWADAPTER_H
