#include "Texture.h"

#include <iostream>
#include <fstream>

#include <stb/stb_image.h>

Texture::Texture(std::string filepath)
{   
    this->filepath = filepath;
    // Generate the texture on the gpu;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Repeat the image if it is too small
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // Pixelate the image instead of blurring
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    stbi_set_flip_vertically_on_load(true);
    unsigned char *image = stbi_load(filepath.c_str(), &width, &height, &channels, 0);

    if (image != nullptr)
    {
        if(channels == 3){
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
        }else if (channels == 4){
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
        }else {
            exit(-1);
        }
    }
    else
    {
        std::cerr << "Texture error: could not load image at " << filepath << std::endl;
        exit(-1);
    }

    stbi_image_free(image);
}
void Texture::bind(){
    glBindTexture(GL_TEXTURE_2D, textureID);
}