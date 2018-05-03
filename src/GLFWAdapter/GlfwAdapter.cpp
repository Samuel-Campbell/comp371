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
    glewExperimental = GL_TRUE;
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

    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
    }
    fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
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
void GlfwAdapter::run(Shader* shader, float vertices[], unsigned int indices[], int verticesSize, int indicesSize){
    unsigned int shaderProgram = shader->makeShaderProgram();
    delete shader;

    setupVertex(vertices, indices, verticesSize, indicesSize);

    while(!glfwWindowShouldClose(window)) {
        processInput();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // draw our first triangle
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);

        glDrawElements(GL_TRIANGLES, indicesSize / sizeof(int), GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteShader(shaderProgram);
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
void GlfwAdapter::processInput() {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}


void GlfwAdapter::setupVertex(float vertices[], unsigned int indices[], int verticesSize, int indicesSize){

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, verticesSize, vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);


    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}
