#pragma once
#ifndef SLOTH_WINDOW_H_
#define SLOTH_WINDOW_H_


#include <GL/glew.h>
#include <GLFW/glfw3.h>
namespace sloth {
	namespace graphics {

#define MAX_KEYS 1024
#define MAX_MOUSE_BOTTON 32

		class Window
		{
		private:
			int m_Width, m_Height;
			const char *m_Title;
			GLFWwindow *m_Window;
			bool m_Closed;

			double m_CursorPosX, m_CursorPosY;
			bool m_Keys[MAX_KEYS];
			bool m_MouseButtons[MAX_MOUSE_BOTTON];
		public:
			Window(const char *name, int width, int height);
			~Window();
			void clear() const;
			bool closed() const;
			void update();

			inline int getWidth() const { return m_Width; }
			inline int getWindth() const { return m_Height; }
			bool isKeyPressed(unsigned int keycode) const;
			bool isMouseButtonPressed(unsigned int keycode) const;
			void getCursorPos(double &x, double &y) const;

		private:
			bool init();
			friend static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
			friend static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
			friend static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
		};
	}
}
#endif // !SLOTH_WINDOW_H_
