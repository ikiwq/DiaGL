#include "Window.h"

#include <iostream>

#include "MouseListener.h"
#include "KeyListener.h"
#include "../scene/Scene.h"

#include "../scene/LevelEditorScene.h"

/*
#include "LevelScene.h"
*/

Window* Window::instance = nullptr;

Scene* Window::currentScene;

Window::Window() {
	width = 1280;
	height = 720;
	title = "ArtemisGL example";

	r = 1.0;
	g = 1.0;
	b = 1.0;
	a = 1.0;
}

Window* Window::getInstance() {
	if (instance == nullptr) {
		instance = new Window();
	}
	return instance;
}

void Window::init() {
	if (!glfwInit()) {
		std::cerr << "Unable to initialize GLFW \n";
		exit(-1);
	}

	configureGLFW();
}

void Window::configureGLFW() {
	//Set window hints (closing, resizing ecc..)
	glfwDefaultWindowHints();
	//Until we finish the configuration, we won't show the window
	glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
	glfwWindowHint(GLFW_MAXIMIZED, GLFW_FALSE);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Create the window
	applicationWindow = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);

	if (applicationWindow == nullptr) {
		std::cerr << "Unable to create GLFW window.";
		exit(-1);
	}

	configureCallbacks();

	//Make the OpenGL context current
	glfwMakeContextCurrent(applicationWindow);
	//Initialize GLAD
	if (!gladLoadGL()) {
		std::cerr << "Could not initialize GLAD";
		exit(-1);
	}

	//Disable V-Sync
	glfwSwapInterval(1);

	//Now we can show the window
	glfwShowWindow(applicationWindow);
	changeScene(0);
}

void Window::configureCallbacks() {
	
	glfwSetCursorPosCallback(applicationWindow, MouseListener::mousePositionCallback);
	glfwSetMouseButtonCallback(applicationWindow, MouseListener::mouseButtonCallback);
	glfwSetScrollCallback(applicationWindow, MouseListener::mouseScrollCallback);

	glfwSetKeyCallback(applicationWindow, KeyListener::keyCallBack);
}

void Window::loop() {
	
	float beginTime = (float)glfwGetTime();
	float endTime = (float)glfwGetTime();
	float dt = beginTime - endTime;

	while (!glfwWindowShouldClose(applicationWindow)) {
		glfwPollEvents();

		glClearColor(r, g, b, a);
		glClear(GL_COLOR_BUFFER_BIT);
		currentScene->update(dt);

		endTime = (float)glfwGetTime();
		dt = endTime - beginTime;
		beginTime = endTime;

		// std::cout << 1.0 / dt << std::endl;

		glfwSwapBuffers(applicationWindow);
	}
	
}

void Window::changeScene(int newScene) {
	delete currentScene;
	switch (newScene) {
	case 0:
		currentScene = new LevelEditorScene();
		currentScene->init();
		currentScene->start();
		break;
	/*case 1:
		currentScene = new LevelScene();
		currentScene->init();
		break;
	*/
	default:
		std::cerr << "Unkown scene" + newScene << "\n";
	}
}

Scene* Window::getScene(){
	return getInstance()->currentScene;
}