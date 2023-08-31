#pragma once
#include <array>
#include <GLFW/glfw3.h>

class KeyListener {
private:
	static KeyListener* instance;
	std::array<bool, 350> keyPressed = std::array<bool, 350>();

public:
	static KeyListener* getInstance();

	static void keyCallBack(GLFWwindow* window, int key, int scancode, int action, int mods);

	static bool isKeyPressed(int keyCode);

private:
	KeyListener();
};
