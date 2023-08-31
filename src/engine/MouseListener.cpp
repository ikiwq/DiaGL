#include "MouseListener.h"

MouseListener* MouseListener::instance = nullptr;

MouseListener::MouseListener() {
	scrollX = 0.0;
	scrollY = 0.0;

	xPos = 0.0;
	yPos = 0.0;
	lastX = 0.0;
	lastY = 0.0;

	dragging = false;
}

MouseListener* MouseListener::getInstance(){
	if (instance == nullptr) {
		instance = new MouseListener();
	}
	return instance;
}

void MouseListener::mousePositionCallback(GLFWwindow* window, double xPos, double yPos) {

	getInstance()->lastX = getInstance()->xPos;
	getInstance()->lastY = getInstance()->yPos;

	getInstance()->xPos = xPos;
	getInstance()->yPos = yPos;

	getInstance()->dragging = getInstance()->mouseButtonDown(0) || getInstance()->mouseButtonDown(1) || getInstance()->mouseButtonDown(2);
}

void MouseListener::mouseButtonCallback(GLFWwindow* window, int button, int action, int modifiers) {
	if (button >= getInstance()->mouseButtonPressed.size()) return;
	
	if (action == GLFW_PRESS) getInstance()->mouseButtonPressed[button] = true;

	if (action == GLFW_RELEASE) {
		getInstance()->mouseButtonPressed[button] = false;
		getInstance()->dragging = false;
	}
}

void MouseListener::mouseScrollCallback(GLFWwindow* window, double xOffset, double yOffset) {
	getInstance()->scrollX = xOffset;
	getInstance()->scrollY = yOffset;
}

void MouseListener::endFrame() {
	getInstance()->scrollX = 0;
	getInstance()->scrollY = 0;

	getInstance()->lastX = getInstance()->xPos;
	getInstance()->lastY = getInstance()->yPos;
}