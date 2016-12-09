#include "window.h"
#include <iostream>
namespace sloth { namespace graphics {

	void window_resize_callback(GLFWwindow *window, int width, int height);
	void key_callback(GLFWwindow * window, int key, int scancode, int action, int mods);
	void mouse_button_callback(GLFWwindow * window, int button, int action, int mods);
	void cursor_position_callback(GLFWwindow * window, double xpos, double ypos);

	Window::Window(const char * title, int width, int height)
	{
		m_Title = title;
		m_Width = width;
		m_Height = height;
		if (!init())
			glfwTerminate();

		for (int i = 0; i < MAX_KEYS; ++i)
		{
			m_Keys[i] = false;
		}

		for (int i = 0; i < MAX_MOUSE_BOTTON; ++i)
		{
			m_MouseButtons[i] = false;
		}

		m_CursorPosX = 0.0;
		m_CursorPosY = 0.0;
	}

	Window::~Window()
	{
		glfwTerminate();
	}

	void Window::clear() const
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	bool Window::closed() const
	{
		return glfwWindowShouldClose(m_Window) == 1;
	}

	void Window::update()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	bool Window::isKeyPressed(unsigned int keycode) const
	{
		// TODO: log in
		if (keycode >= MAX_KEYS)
			return false;
		return m_Keys[keycode];
	}

	bool Window::isMouseButtonPressed(unsigned int keycode) const
	{
		// TODO: log in
		if (keycode >= MAX_MOUSE_BOTTON)
			return false;
		return m_MouseButtons[keycode];
	}

	void Window::getCursorPos(double & x, double & y) const
	{
		x = m_CursorPosX;
		y = m_CursorPosY;
	}

	bool Window::init()
	{
		if (!glfwInit()) {
			std::cout << "Failed to initialize GLFW!" << std::endl;
			return false;
		}
		m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, nullptr, nullptr);
		if (!m_Window) {
			std::cout << "Failed to create GLFW window!" << std::endl;
			return false;
		}
		//glfwWindowHint(GL_MAJOR_VERSION, 3);
		//glfwWindowHint(GL_MINOR_VERSION, 3);
		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, this);
		glfwSetWindowSizeCallback(m_Window, window_resize_callback);
		glfwSetKeyCallback(m_Window, key_callback);
		glfwSetMouseButtonCallback(m_Window, mouse_button_callback);
		glfwSetCursorPosCallback(m_Window, cursor_position_callback);
		glewExperimental = GL_TRUE;
		glewInit();
		return true;
	}

	void window_resize_callback(GLFWwindow *window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}

	void key_callback(GLFWwindow * window, int key, int scancode, int action, int mods)
	{
		Window *win = (Window*) glfwGetWindowUserPointer(window);
		win->m_Keys[key] = action != GLFW_RELEASE;
	}

	void mouse_button_callback(GLFWwindow * window, int button, int action, int mods)
	{
		Window *win = (Window*)glfwGetWindowUserPointer(window);
		win->m_MouseButtons[button] = action != GLFW_RELEASE;
	}

	void cursor_position_callback(GLFWwindow * window, double xpos, double ypos)
	{
		Window *win = (Window*)glfwGetWindowUserPointer(window);
		win->m_CursorPosX = xpos;
		win->m_CursorPosY = ypos;
	}


} }
