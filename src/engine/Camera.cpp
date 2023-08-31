#include "../engine/Camera.h"

#include "glm/gtc/matrix_transform.hpp"
#include "../engine/Window.h"

void Camera::adjustProjection(){
    this->projectionMatrix = glm::ortho(0.0f, (float)Window::getInstance()->width, 0.0f, (float)Window::getInstance()->height, 0.0f, 100.0f);
}

glm::mat4 Camera::getViewMatrix(){
    glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
    this->viewMatrix = glm::lookAt(glm::vec3(position.x, position.y, 20.0f),
        cameraFront + glm::vec3(position.x, position.y, 0.0f),
        cameraUp * scaleFactor);
        
    return glm::scale(this->viewMatrix, glm::vec3(scaleFactor));
};