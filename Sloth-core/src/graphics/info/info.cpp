#include "info.h"
#include <iostream>
namespace sloth { namespace graphics {
	int Input::windowWidth = SCREEN_WIDTH, Input::windowHeight = SCREEN_HEIGHT;
	double Input::cursorPosX = 0.0, Input::cursorPosY = 0.0;
	double Input::lastCursorPosX = 0.0, Input::lastCursorPosY = 0.0;
	std::vector<bool> Input::keys = std::vector<bool>(MAX_KEYS, false);
	double Input::scrollX = 0.0, Input::scrollY = 0.0;

	void window_resize_callback(GLFWwindow *window, int width, int height)
	{
		SlothWindow *win = (SlothWindow*)glfwGetWindowUserPointer(window);
		win->setWidth(width);
		win->setHeight(height);
		glViewport(0, 0, width, height);
		Input::windowWidth = width;
		Input::windowHeight = height;
	}

	void key_callback(GLFWwindow * window, int key, int scancode, int action, int mods)
	{
		SlothWindow *win = (SlothWindow*)glfwGetWindowUserPointer(window);
		Input::keys[key] = action != GLFW_RELEASE;
		if (action == GLFW_PRESS && !Input::keys[key])
			Input::keys[key] = true;
		else if (action == GLFW_RELEASE)
			Input::keys[key] = false;
	}

	void cursor_position_callback(GLFWwindow * window, double xpos, double ypos)
	{
		Input::lastCursorPosX = Input::cursorPosX;
		Input::lastCursorPosY = Input::cursorPosY;
		Input::cursorPosX = xpos;
		Input::cursorPosY = ypos;
	}

	void scroll_callback(GLFWwindow * window, double xoffset, double yoffset)
	{
		Input::scrollX += xoffset;
		Input::scrollY += yoffset;
	}

} }