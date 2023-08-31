#pragma once

#include <glm/glm.hpp>

class Transform {
public:
    glm::vec2 position;
    glm::vec2 scale;
    float rotation;

    Transform(){
    }

    Transform(glm::vec2 position){
        init(position, glm::vec2(), 0.0f);
    }

    Transform(glm::vec2 position, glm::vec2 scale){
        init(position, scale, 0.0f);
    }

    Transform(glm::vec2 position, glm::vec2 scale, float rotation) {
        init(position, scale, rotation);
    }

    void init(glm::vec2 position, glm::vec2 scale, float rotation){
        this->position = position;
        this->scale = scale;
        this->rotation = rotation;
    }
};