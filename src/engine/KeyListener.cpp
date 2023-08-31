#include "KeyListener.h"
#include <iostream>

KeyListener* KeyListener::instance = nullptr;

KeyListener::KeyListener(){}

KeyListener* KeyListener::getInstance() {
	if (instance == nullptr) {
		instance = new KeyListener();
	}
	return instance;
}

void KeyListener::keyCallBack(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key >= getInstance()->keyPressed.size()) return;
	if (action == GLFW_PRESS) {
		getInstance()->keyPressed[key] = true;
	}
	if (action == GLFW_RELEASE) {
		getInstance()->keyPressed[key] = false;
	}
}

bool KeyListener::isKeyPressed(int keyCode) {
	return getInstance()->keyPressed[keyCode];
}