//
// Created by charmander on 03/05/18.
//

#include <iostream>
#include "GlfwAdapter.h"

/**
 * Default Constructor
 */
GlfwAdapter::GlfwAdapter() {

}

/**
 * 1) Initializes GLFW
 *      If it fails then return false
 * 2) Sets version to 3.0+
 * 3) Create window of size WIDTH X HEIGHT
 *      If window creation fails then return false
 * 4) Make rendering size of window
 * 5) Override the framebuffer_size_callback function
 */
bool GlfwAdapter::init() {
    if (!glfwInit()){
        std::cout << "Failed to initialize GLFW" << std::endl;
        return false;
    }

    // OpenGL version 3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPENGL_VERSION);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPENGL_VERSION);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME, NULL, NULL);
    if (window == NULL){
        std::cout << "Failed to create window" << std::endl;
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(window);
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    return true;
}


/**
 * Main class method
 *
 * Loops until window is closed
 *
 * Takes inputs from a user
 *      ESC: closes window
 *
 * Safely terminate GLFW at the end
 */
void GlfwAdapter::run(){
    while(!glfwWindowShouldClose(window)) {
        processInput(window);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
}

/**
 * Event handler on window resize
 *
 * @param window GLFWwindow object
 * @param width width of GLFWwindow
 * @param height height of GLFWwindow
 */
void GlfwAdapter::framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

/**
 * Event handler on input
 *
 * ESC: closes window
 *
 * @param window GLFWwindow object
 */
void GlfwAdapter::processInput(GLFWwindow *window) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}