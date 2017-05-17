#pragma once

/**
	Specifically for processing keys and mouse information
*/
#include <sloth.h>
namespace sloth {

	class Input
	{
	public:
		static int windowWidth, windowHeight;
		static double cursorPosX, cursorPosY;
		static double lastCursorPosX, lastCursorPosY;
		static std::vector<bool> keys;
		static double scrollX, scrollY;
	};

	void window_resize_callback(GLFWwindow *window, int width, int height);
	void key_callback(GLFWwindow * window, int key, int scancode, int action, int mods);
	void cursor_position_callback(GLFWwindow * window, double xpos, double ypos);
	void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
} 