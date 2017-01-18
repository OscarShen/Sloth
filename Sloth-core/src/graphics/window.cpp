#include "window.h"
#include <iostream>
namespace sloth { namespace graphics {

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
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
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
		glfwSetMouseButtonCallback(m_Window, mouse_button_callback);
		glfwSetCursorPosCallback(m_Window, cursor_position_callback);
		glfwSwapInterval(0);
		glewExperimental = GL_TRUE;
		glewInit();
		return true;
	}

} }
