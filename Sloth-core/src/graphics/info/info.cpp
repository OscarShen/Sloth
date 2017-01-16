#include "info.h"
namespace sloth { namespace graphics {
	double Input::cursorPosX = 0.0, Input::cursorPosY = 0.0;
	double Input::lastCursorPosX = 0.0, Input::lastCursorPosY = 0.0;
	std::vector<bool> Input::keys = std::vector<bool>(MAX_KEYS, false);
	std::vector<bool> Input::mouseButtons = std::vector<bool>(MAX_MOUSE_BOTTON, false);

	void window_resize_callback(GLFWwindow *window, int width, int height)
	{
		SlothWindow *win = (SlothWindow*)glfwGetWindowUserPointer(window);
		win->setWidth(width);
		win->setHeight(height);
		glViewport(0, 0, width, height);
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

	void mouse_button_callback(GLFWwindow * window, int button, int action, int mods)
	{
		SlothWindow *win = (SlothWindow*)glfwGetWindowUserPointer(window);
		if (action == GLFW_PRESS && !Input::mouseButtons[button])
			Input::mouseButtons[button] = true;
		else if(action == GLFW_RELEASE)
			Input::mouseButtons[button] = false;
	}

	void cursor_position_callback(GLFWwindow * window, double xpos, double ypos)
	{
		SlothWindow *win = (SlothWindow*)glfwGetWindowUserPointer(window);
		Input::cursorPosX = xpos;
		Input::cursorPosY = ypos;
	}


	bool Input::isMouseButtonPressed(unsigned int keycode)
	{
		// TODO: log in
		if (keycode >= MAX_MOUSE_BOTTON)
			return false;
		return mouseButtons[keycode];
	}

	void Input::getCursorPos(double & x, double & y)
	{
		x = cursorPosX;
		y = cursorPosY;
	}

	void Input::process(SlothWindow * window, Camera *camera, float deltaTime)
	{
		float cameraSpeed = deltaTime * 10;
		if (keys[GLFW_KEY_W])
			camera->do_movement(CameraMovement::MOVEFORWARD, deltaTime);
		if (keys[GLFW_KEY_S])
			camera->do_movement(CameraMovement::MOVEBACKWARD, deltaTime);
		if (keys[GLFW_KEY_A])
			camera->do_movement(CameraMovement::MOVELEFT, deltaTime);
		if (keys[GLFW_KEY_D])
			camera->do_movement(CameraMovement::MOVERIGHT, deltaTime);
		if (keys[GLFW_KEY_ESCAPE])
			window->close();

		if (camera->firstMouse)
		{
			lastCursorPosX = cursorPosX;
			lastCursorPosY = cursorPosY;
			camera->firstMouse = false;
		}
		camera->do_mouse(cursorPosX - lastCursorPosX, lastCursorPosY - cursorPosY);
		lastCursorPosX = cursorPosX;
		lastCursorPosY = cursorPosY;
	}


	bool Input::isKeyPressed(unsigned int keycode)
	{
		// TODO: log in
		if (keycode >= MAX_KEYS)
			return false;
		return keys[keycode];
	}
} }