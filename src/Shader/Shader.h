#include <iostream>
#include <fstream>
#include <string.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <tgmath.h>
#include <zconf.h>

#ifndef COMP371_SHADER_H
#define COMP371_SHADER_H


class Shader {
public:
    Shader();
    unsigned int makeShaderProgram();
    void updateColor();

private:
    unsigned int vertexShader;
    unsigned int fragmentShader;
    unsigned int shaderProgram;
    const std::string vertexShaderFile = "/src/Shader/vertex_shader.txt";
    const std::string fragmentShaderFile = "/src/Shader/fragment_shader.txt";

    void makeVertexShader();
    void makeFragmentShader();
    std::string readFile(std::string fileName);
    std::string getCurrentWorkingDir();
};


#endif //COMP371_SHADER_H
