#include "Shader.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <glad/glad.h>

Shader::Shader(std::string filepath) {
    setShadersSource(filepath);
}

void Shader::setShadersSource(std::string filepath)
{
    shadersFilepath = filepath;

    std::ifstream shaderFile(filepath);

    if (!shaderFile.is_open())
    {
        std::cerr << "Error opening shader file." << std::endl;
        exit(-1);
    }

    std::string line;
    std::stringstream vertexShaderStream;
    std::stringstream fragmentShaderStream;
    std::stringstream *currentStream = nullptr;

    while (std::getline(shaderFile, line))
    {
        if (line.find("#type vertex") != std::string::npos)
        {
            currentStream = &vertexShaderStream;
            continue;
        }
        if (line.find("#type fragment") != std::string::npos)
        {
            currentStream = &fragmentShaderStream;
            continue;
        }
        if (currentStream)
        {
            (*currentStream) << line << '\n';
        }
    }

    vertexShaderSource = vertexShaderStream.str();
    fragmentShaderSource = fragmentShaderStream.str();
};

void Shader::compile()
{
    compileVertexShader();
    compileFragmentShader();
    linkShaderProgram();
};

void Shader::compileVertexShader()
{
    vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    const char *source = vertexShaderSource.data();
    glShaderSource(vertexShaderID, 1, &source, NULL);
    glCompileShader(vertexShaderID);

    GLint vertexShaderCompileStatus;
    glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &vertexShaderCompileStatus);

    if (vertexShaderCompileStatus == GL_FALSE)
    {
        GLint infoLogLength;
        glGetShaderiv(vertexShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
        GLchar *infoLog = new GLchar[infoLogLength];
        glGetShaderInfoLog(vertexShaderID, infoLogLength, NULL, infoLog);
        std::cerr << "Vertex shader compilation error:\n"
                  << infoLog << std::endl;
        delete[] infoLog;
        exit(-1);
    }

    delete source;
}

void Shader::compileFragmentShader()
{
    fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    const char *source = fragmentShaderSource.data();
    glShaderSource(fragmentShaderID, 1, &source, NULL);
    glCompileShader(fragmentShaderID);

    GLint fragmentShaderCompileStatus;
    glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &fragmentShaderCompileStatus);

    if (fragmentShaderCompileStatus == GL_FALSE)
    {
        GLint infoLogLength;
        glGetShaderiv(fragmentShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
        GLchar *infoLog = new GLchar[infoLogLength];
        glGetShaderInfoLog(fragmentShaderID, infoLogLength, NULL, infoLog);
        std::cerr << "Fragment shader compilation error:\n"
                  << infoLog << std::endl;
        delete[] infoLog;
        exit(-1);
    }

    delete source;
};

void Shader::linkShaderProgram()
{
    shaderProgramID = glCreateProgram();
    glAttachShader(shaderProgramID, vertexShaderID);
    glAttachShader(shaderProgramID, fragmentShaderID);

    glLinkProgram(shaderProgramID);

    GLint programLinkingStatus;
    glGetProgramiv(shaderProgramID, GL_LINK_STATUS, &programLinkingStatus);

    if (programLinkingStatus == GL_FALSE)
    {
        GLint infoLogLength;
        glGetShaderiv(shaderProgramID, GL_INFO_LOG_LENGTH, &infoLogLength);
        GLchar *infoLog = new GLchar[infoLogLength];
        glGetShaderInfoLog(shaderProgramID, infoLogLength, NULL, infoLog);
        std::cerr << "Shader linking error:\n"
                  << infoLog << std::endl;
        delete[] infoLog;
        exit(-1);
    }
}

void Shader::use()
{
    if(!beingUsed){
        glUseProgram(shaderProgramID);
        beingUsed = true;
    }
}

void Shader::detach()
{
    glUseProgram(0);
    beingUsed = false;
}

void Shader::uploadMat4f(std::string varName, const glm::mat4 mat4){
    int varLocation = glGetUniformLocation(shaderProgramID, varName.c_str());
    use();
    glUniformMatrix4fv(varLocation, 1, GL_FALSE, &mat4[0][0]);
};

void Shader::uploadTexture(std::string varName, int slot){
    int varLocation = glGetUniformLocation(shaderProgramID, varName.c_str());
    use();
    glUniform1i(varLocation, slot);
}

void Shader::uploadIntArray(std::string varName, int* intArray) {
    int varLocation = glGetUniformLocation(shaderProgramID, varName.c_str());
    use();
    glUniform1iv(varLocation, sizeof(intArray), intArray);
}