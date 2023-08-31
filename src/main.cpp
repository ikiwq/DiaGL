#include "engine/Window.h"

int main() {
	Window* window = Window::getInstance();
	window->run();
}