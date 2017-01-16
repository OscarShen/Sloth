#pragma once
#ifndef SLOTH_WINDOW_H_
#define SLOTH_WINDOW_H_

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "camera/camera.h"
#include "info/info.h"
namespace sloth { namespace graphics {

#define MAX_KEYS 1024
#define MAX_MOUSE_BOTTON 32

	class SlothWindow
	{
	private:
		int m_Width, m_Height;
		const char *m_Title;
		GLFWwindow *m_Window;

	public:
		SlothWindow(const char *name, int width, int height);
		~SlothWindow();
		void clear() const;
		bool closed() const;
		void close();
		void update();

		inline int getWidth() const { return m_Width; }
		inline int getHeight() const { return m_Height; }
		void setWidth(int width) { m_Width = width; }
		void setHeight(int height) { m_Height = height; }

	private:
		bool init();
	};
} }
#endif // !SLOTH_WINDOW_H_
