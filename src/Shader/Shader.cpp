#include "Shader.h"

Shader::Shader(){

}

void Shader::makeVertexShader() {
    std::string text = readFile(vertexShaderFile);
    const char *vertexShaderSource = strdup(text.c_str());

    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    int  success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    else{
        std::cout << "Vertex shader successfully compiled" << std::endl;
    }
}

void Shader::makeFragmentShader() {
    std::string text = readFile(fragmentShaderFile);
    const char *fragmentShaderSource = strdup(text.c_str());

    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    int  success;
    char infoLog[512];
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    else{
        std::cout << "Fragment shader successfully compiled" << std::endl;
    }
}

unsigned int Shader::makeShaderProgram() {
    makeVertexShader();
    makeFragmentShader();

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    int  success;
    char infoLog[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }else{
        std::cout << "Shader Program successfully compiled" << std::endl;
    }

    glUseProgram(shaderProgram);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}

std::string Shader::readFile(std::string fileName) {
    std::string path = getCurrentWorkingDir();
    fileName = path + fileName;
    std::string line;
    std::string text;

    std::ifstream file;

    file.open(fileName);
    if (file.is_open()) {
        while ( getline (file,line) ) {
            text += line + "\n";
        }
        file.close();
    }
    else {
        std::cout << "Unable to open file" << std::endl;
    }

    return text;
}

std::string Shader::getCurrentWorkingDir() {
    char cwd_buffer[2048];
    char* cwd_result = getcwd(cwd_buffer, 2048);
    std::string path;
    for (int i = 0; cwd_result[i] != '\0'; i++){
        path += cwd_result[i];
    }
    path = path.substr(0, path.find_last_of('/'));
    return path;
}

void Shader::updateColor(){
    double timeValue = glfwGetTime();
    auto greenValue = float((sin(timeValue) / 2.0f) + 0.5f);
    int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
    glUseProgram(shaderProgram);
    glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
}