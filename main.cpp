#include <iostream>
#include "GLFWAdapter/GlfwAdapter.h"

int main() {
    auto* glfwadapter = new GlfwAdapter();
    if (glfwadapter->init()){
        glfwadapter->run();
    }
    return 0;
}
