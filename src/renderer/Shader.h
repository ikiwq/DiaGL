#pragma once

#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Shader
{
public:
    int shaderProgramID;
    int vertexShaderID;
    int fragmentShaderID;

    std::string shadersFilepath;

    std::string vertexShaderSource;
    std::string fragmentShaderSource;

    bool beingUsed = false;

public:
    Shader(std::string filepath);

    void compile();

    void use();

    void detach();

    void uploadMat4f(std::string varName, const glm::mat4 mat4);

    void uploadTexture(std::string varName, int slot);

    void uploadIntArray(std::string varName, int intArray[]);

private:
    void setShadersSource(std::string filepath);

    void compileVertexShader();
    
    void compileFragmentShader();

    void linkShaderProgram();
};