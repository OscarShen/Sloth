#pragma once
#ifndef SLOTH_WINDOW_H
#define SLOTH_WINDOW_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
class Window {
public:
	Window() = default;

	void createWindow(int width, int height, const char *title);

	void render();

	bool shouldClose();

	void stop();

	void dispose();

	double getFrameCap() const;


private:
	GLFWwindow *window;
	int width;
	int height;
	std::string title;
	double frame_cap = 60.0;
};
#endif // !SLOTH_WINDOW_H
