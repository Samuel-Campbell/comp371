#include <GL/glew.h>
#include <GLFW/glfw3.h>

#ifndef COMP371_GLFWADAPTER_H
#define COMP371_GLFWADAPTER_H


class GlfwAdapter {
public:
    GlfwAdapter();
    bool init();
    void run();

private:
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    void processInput(GLFWwindow *window);
    void vertexInput();

    const int OPENGL_VERSION = 3;
    const int WINDOW_WIDTH = 800;
    const int WINDOW_HEIGHT = 600;
    const char* WINDOW_NAME = "Assignment 1";
    GLFWwindow* window;
};


#endif //COMP371_GLFWADAPTER_H
