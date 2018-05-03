#include <iostream>
#include "GLFWAdapter/GlfwAdapter.h"
#include "GLFWAdapter/Shader.h"

int main() {
    float vertices[] = {
            0.5f,  0.5f, 0.0f,  // top right
            0.5f, -0.5f, 0.0f,  // bottom right
            -0.5f, -0.5f, 0.0f,  // bottom left
            -0.5f,  0.5f, 0.0f   // top left
    };

    unsigned int indices[] = {
            0, 1, 3,
            1, 2, 3
    };

    auto* glfwadapter = new GlfwAdapter();
    auto* shader = new Shader();

    if (glfwadapter->init()){
        glfwadapter->run(shader, vertices, indices, sizeof(vertices), sizeof(indices));
    }

    delete shader;
    delete glfwadapter;

    return 0;
}
