#include "window.h"
#include <iostream>
namespace sloth { namespace graphics {

	SlothWindow::SlothWindow(const char * title, int width, int height)
	{
		m_Title = title;
		m_Width = width;
		m_Height = height;
		if (!init())
			glfwTerminate();
	}

	SlothWindow::~SlothWindow()
	{
	}

	void SlothWindow::clear() const
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	bool SlothWindow::closed() const
	{
		return glfwWindowShouldClose(m_Window) != 0;
	}

	void SlothWindow::close()
	{
		glfwDestroyWindow(m_Window);
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
