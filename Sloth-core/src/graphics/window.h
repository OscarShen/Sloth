#pragma once
#ifndef SLOTH_WINDOW_H_
#define SLOTH_WINDOW_H_

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "info/info.h"
#include "../config/macro.h"

namespace sloth { namespace graphics {

	class SlothWindow
	{
	private:
		int m_Width, m_Height;
		const char *m_Title;
		GLFWwindow *m_Window;
		bool m_IsRunning;

	public:
		SlothWindow(const char *name, int width, int height);
		~SlothWindow();
		void clear() const;
		inline bool isRunning() const { return m_IsRunning; }
		void close();
		void update();

		inline int getWidth() const { return m_Width; }
		inline int getHeight() const { return m_Height; }
		inline GLFWwindow* getGLFWwindow() const { return m_Window; }
		void setWidth(int width) { m_Width = width; }
		void setHeight(int height) { m_Height = height; }

	private:
		bool init();
		
		void checkKeyboard();
	};
} }
#endif // !SLOTH_WINDOW_H_
