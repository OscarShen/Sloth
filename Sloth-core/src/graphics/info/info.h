#pragma once

/**
	Specifically for processing keys and mouse information
*/
#include "../window.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
namespace sloth { namespace graphics {

	class SlothWindow;
	class Input
	{
	public:
		static double cursorPosX, cursorPosY;
		static double lastCursorPosX, lastCursorPosY;
		static std::vector<bool> keys;
		static std::vector<bool> mouseButtons;

		static bool isKeyPressed(unsigned int keycode);
		static bool isMouseButtonPressed(unsigned int keycode);
		static void getCursorPos(double &x, double &y);

		static void process(SlothWindow *window, Camera *camera, float deltaTime);
	};

	void window_resize_callback(GLFWwindow *window, int width, int height);
	void key_callback(GLFWwindow * window, int key, int scancode, int action, int mods);
	void mouse_button_callback(GLFWwindow * window, int button, int action, int mods);
	void cursor_position_callback(GLFWwindow * window, double xpos, double ypos);


} }