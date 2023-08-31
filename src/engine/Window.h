#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>

class Scene;

class Window {
public: 
	float r, g, b, a;
	int width;
	int height;
private:
	static Window* instance;

	GLFWwindow* applicationWindow = nullptr;

	static Scene* currentScene;

	std::string title;

public:
	static Window* getInstance();

	void run() {
		init();
		loop();
		clear();
	}

	static void changeScene(int newScene);

	static Scene* getScene();

private:
	Window();

	void init();

	void configureGLFW();

	void configureCallbacks();

	void loop();

	void clear() {
		glfwDestroyWindow(applicationWindow);
		glfwTerminate();
	}
};