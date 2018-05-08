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
 *
 * 2) Sets version to 3.0+
 *
 * 3) Create window of size WIDTH X HEIGHT
 *      If window creation fails then return false
 *
 * 4) Make rendering size of window
 *
 * 5) Override the framebuffer_size_callback function
 *
 * 6) Initialize GLEW
 *      Return False if error
 */
bool GlfwAdapter::init() {
    // ----- 1 -----
    glewExperimental = GL_TRUE;
    if (!glfwInit()){
        std::cout << "Failed to initialize GLFW" << std::endl;
        return false;
    }

    // ----- 2 -----
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPENGL_VERSION);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPENGL_VERSION);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // ----- 3 -----
    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME, NULL, NULL);
    if (window == NULL){
        std::cout << "Failed to create window" << std::endl;
        glfwTerminate();
        return false;
    }

    // ----- 4 -----
    glfwMakeContextCurrent(window);
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    // ----- 5 -----
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // ----- 6 -----
    GLenum err = glewInit();
    if (GLEW_OK != err) {
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
        return false;
    }
    fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));

    return true;
}


/**
 * 1) Create the shader program
 *
 * 2) setup the vertices array object, indices buffer objects and element buffer objects
 *
 * 3) Loop until window is closed
 *      - process inputs
 *      - draw from vertices array object
 *      - refresh on window resize
 *
 * 4) Delete unused objects from Heap
 *
 * @param shader Shader object pointer
 * @param vertices float[] must be n X 3
 * @param indices int[] must be n X 3
 * @param verticesSize
 * @param indicesSize
 */
void GlfwAdapter::run(Shader* shader, float vertices[], unsigned int indices[], int verticesSize, int indicesSize){

    // ----- 1 -----
    unsigned int shaderProgram = shader->makeShaderProgram();

    // ----- 2 -----
    setupVertex(vertices, indices, verticesSize, indicesSize);

    // ----- 3 -----
    while(!glfwWindowShouldClose(window)) {
        processInput();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);

        // update uniform color
        shader->updateColor();

        // Render triangle
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // swap buffers and poll IO events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // ----- 4 -----
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteShader(shaderProgram);
    delete shader;
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

/**
 * 1) Generate  buffer IDs for vertices array object, vertices buffer object, and element buffer object
 *
 * 2) Bind buffer types and data
 *
 * 3) Specify to OpenGL how to interpret the vertex buffer data whenever a drawing call is made
 *
 * 4) clean up buffers
 *
 * @param vertices float[] must be n X 3
 * @param indices int[] must be n X 3
 * @param verticesSize
 * @param indicesSize
 */
void GlfwAdapter::setupVertex(float vertices[], unsigned int indices[], int verticesSize, int indicesSize){

    // ----- 1 -----
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // ----- 2 -----
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, verticesSize, vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, indices, GL_STATIC_DRAW);

    // ----- 3 -----
    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);

    // ----- 4 -----
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
