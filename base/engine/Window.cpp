#include "Window.h"
#include "Input.h"

void Window::createWindow(int width, int height, const char * title)
{
	this->width = width;
	this->height = height;
	this->title = std::string(title);
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	this->window = glfwCreateWindow(width, height, title, nullptr, nullptr);
	glfwMakeContextCurrent(this->window);

	void (*keyCallback)(GLFWwindow * window, int key, int scancode, int action, int mode);
	keyCallback = & Input::key_callback;
	glfwSetKeyCallback(window, keyCallback);

	void (*mouseCallback) (GLFWwindow * window, double xpos, double ypos);
	mouseCallback = &Input::mouse_callback;

	glfwSetCursorPosCallback(window, mouseCallback);

	glewExperimental = GL_TRUE;
	glewInit();
	glViewport(0, 0, width, height);
}

void Window::render()
{

	glfwPollEvents();
	glfwSwapBuffers(this->window);
}

bool Window::shouldClose()
{
	if (glfwWindowShouldClose(this->window))
		return true;
	else
		return false;
}

void Window::stop()
{
	glfwSetWindowShouldClose(this->window, GL_TRUE);
}

void Window::dispose()
{
	glfwTerminate();
}

double Window::getFrameCap() const
{
	return frame_cap;
}
