//
// Created by charmander on 03/05/18.
//

#ifndef COMP371_SHADER_H
#define COMP371_SHADER_H


class Shader {
public:
    Shader();
    unsigned int makeShaderProgram();

private:
    unsigned int vertexShader;
    unsigned int fragmentShader;
    unsigned int shaderProgram;

    void makeVertexShader();
    void makeFragmentShader();
};


#endif //COMP371_SHADER_H
