#pragma once

#include <array>
#include <GLFW/glfw3.h>

class MouseListener
{
private:
	static MouseListener *instance;
	double scrollX, scrollY;
	double xPos, yPos, lastY, lastX;

	std::array<int, 3> mouseButtonPressed = std::array<int, 3>();
	bool dragging;

	float dragSensitivity = 1;
	float zoomSensitivity = 0.2f;

public:
	static MouseListener *getInstance();

	static void mousePositionCallback(GLFWwindow *window, double xPos, double yPos);

	static void mouseButtonCallback(GLFWwindow *window, int button, int action, int modifiers);

	static void mouseScrollCallback(GLFWwindow *window, double xOffset, double yOffset);

	static void endFrame();

	static float getX()
	{
		return (float)getInstance()->xPos;
	}

	static float getY()
	{
		return (float)getInstance()->yPos;
	}

	static float getDx()
	{
		return (float)(getInstance()->lastX - getInstance()->xPos);
	}

	static float getDy()
	{
		return (float)(getInstance()->lastY - getInstance()->yPos);
	}

	static float getScrollX()
	{
		return (float)getInstance()->scrollX * getInstance()->zoomSensitivity;
	}

	static float getScrollY()
	{
		return (float)getInstance()->scrollY * getInstance()->zoomSensitivity;
	}

	static bool isDragging()
	{
		return getInstance()->isDragging;
	}

	static bool mouseButtonDown(int button)
	{
		if (button >= getInstance()->mouseButtonPressed.size())
			return 0;
		return getInstance()->mouseButtonPressed[button];
	}

private:
	MouseListener();
};