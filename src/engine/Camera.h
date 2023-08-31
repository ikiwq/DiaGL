#pragma once

#include  <glm/glm.hpp>

class Camera {
private:
    glm::mat4 projectionMatrix, viewMatrix;
    glm::vec2 position;
    float scaleFactor = 1;
public:
    Camera(glm::vec2 position){
        this->position = position;
        this->projectionMatrix = glm::mat4();
        this->viewMatrix = glm::mat4();
        this->adjustProjection();
    }

    void adjustProjection();

    glm::mat4 getViewMatrix();

    glm::mat4 getProjectionMatrix(){
        return this->projectionMatrix;
    }

    glm::vec2 getPosition(){
        return this->position;
    }

    void setPosition(glm::vec2 position){
        this->position = position;
    }

    void setPosition(float x, float y){
        this->position = glm::vec2(x, y);
    }

    float getScaleFactor(){
        return this->scaleFactor;
    }

    void setScaleFactor(float scaleFactor){
        if(scaleFactor <= 0) return ;
        this->scaleFactor = scaleFactor;
    }
};