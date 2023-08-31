#pragma once

#include <glad/glad.h>
#include <string>

class Texture {
public:
    int width, height, channels;
private:
    std::string filepath;
    GLuint textureID;

public:
    Texture(std::string filepath);

    void bind();

    void unbind() {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    int getId() {
        return textureID;
    }
};