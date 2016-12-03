#include "Input.h"
std::array<bool, 512> Input::keys;
std::array<double, 2> Input::mouse;
bool Input::firstMouse = true;
double Input::lastX;
double Input::lastY;

bool Input::isKeyPressed(int code)
{
	return keys[code];
}

double Input::mouseMove(int code)
{
	return mouse[code];
}

void Input::key_callback(GLFWwindow * window, int key, int scancode, int action, int mode)
{
	if (action == SLOTH_PRESS)
		Input::keys[key] = true;
	else if (action == SLOTH_RELEASE) {
		Input::keys[key] = false;
	}
}

void Input::mouse_callback(GLFWwindow * window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	double xoffset = xpos - lastX;
	double yoffset = lastY - ypos;

	lastX = xpos;
	lastY = ypos;
	Input::mouse[SLOTH_MOUSE_X_OFFSET] = xpos;
	Input::mouse[SLOTH_MOUSE_Y_OFFSET] = ypos;
}