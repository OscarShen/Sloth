#include "window.h"
#include <iostream>
namespace sloth {

	SlothWindow::SlothWindow(const char * title, int width, int height)
		:m_Title(title), m_Width(width), m_Height(height), m_Window(nullptr), 
		m_IsRunning(false)
	{
		if (!init()) {
			// TODO : Add to log!
			std::cout << "Initial failed!" << std::endl;
		}
		else {
			m_IsRunning = true;
			glClearColor(DEFUALT_CLEAR_COLOR_RED, DEFUALT_CLEAR_COLOR_GREEN, DEFUALT_CLEAR_COLOR_BLUE, 1.0f);
		}
	}

	SlothWindow::~SlothWindow()
	{
		if (m_Window)
			glfwDestroyWindow(m_Window);
	}

	void SlothWindow::clear() const
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void SlothWindow::close()
	{
		m_IsRunning = false;
	}

	void SlothWindow::update()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
		checkKeyboard();
	}

	bool SlothWindow::init()
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
		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, this);
		glfwSetWindowSizeCallback(m_Window, window_resize_callback);
		glfwSetKeyCallback(m_Window, key_callback);
		glfwSetCursorPosCallback(m_Window, cursor_position_callback);
		glfwSetScrollCallback(m_Window, scroll_callback);
		glfwSwapInterval(0);
		glewExperimental = GL_TRUE;
		glewInit();
		glEnable(GL_MULTISAMPLE);
		return true;
	}

	void SlothWindow::checkKeyboard()
	{
		if (Input::keys[GLFW_KEY_ESCAPE])
			close();
	}

} 
