#include <iostream>
#include "GLFWAdapter/GlfwAdapter.h"
#include "Shader/Shader.h"

int main() {

    float vertices[] = {
            0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
            -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f
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

    return 0;
}
