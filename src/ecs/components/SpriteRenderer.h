#pragma once

#include "../Component.h"

#include <iostream>
#include <array>

#include <glm/glm.hpp>

#include "../components/Sprite.h"

class Texture;

class SpriteRenderer : public Component
{
public:
private:
    glm::vec4 color;
    Sprite* sprite;

public:
    SpriteRenderer(glm::vec4 color) {
        this->color = color;
        this->sprite = nullptr;
    }

    SpriteRenderer(Sprite* sprite) {
        this->color = glm::vec4(1, 1, 1, 1);
        this->sprite = sprite;
    }

    bool init()
    {
        return true;
    }

    void update(float dt)
    {
    }

    glm::vec4 getColor() {
        return color;
    }

    Texture* getTexture() {
        return sprite->getTexture();
    }

    std::array<glm::vec2, 4> getTextureCoords() {
        return sprite->getTextureCoords();
    }
};