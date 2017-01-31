#include "camera.h"

namespace sloth { namespace graphics {

	void Camera::process(SlothWindow * window)
	{
		process_keyboard(window);
		process_mouse(window);
	}

	void Camera::process_keyboard(SlothWindow * window)
	{
		if (Input::keys[GLFW_KEY_UP])
			do_movement(CameraMovement::MOVEFORWARD, util::Timer::deltaFrameTime);
		if (Input::keys[GLFW_KEY_DOWN])
			do_movement(CameraMovement::MOVEBACKWARD, util::Timer::deltaFrameTime);
		if (Input::keys[GLFW_KEY_LEFT])
			do_movement(CameraMovement::MOVELEFT, util::Timer::deltaFrameTime);
		if (Input::keys[GLFW_KEY_RIGHT])
			do_movement(CameraMovement::MOVERIGHT, util::Timer::deltaFrameTime);
		if (Input::keys[GLFW_KEY_ESCAPE])
			window->close();
	}

	void Camera::do_movement(CameraMovement direction, float deltaTime)
	{
		float v = deltaTime * m_MoveSpeed;
		switch (direction)
		{
		case MOVEFORWARD:
			m_Position += m_Front * v;
			break;
		case MOVEBACKWARD:
			m_Position -= m_Front * v;
			break;
		case MOVELEFT:
			m_Position -= m_Right * v;
			break;
		case MOVERIGHT:
			m_Position += m_Right * v;
			break;
		default:
			break;
		}
	}

	void Camera::process_mouse(SlothWindow * window)
	{
		if (firstMouse)
		{
			Input::lastCursorPosX = Input::cursorPosX;
			Input::lastCursorPosY = Input::cursorPosY;
			firstMouse = false;
		}
		do_mouse(Input::cursorPosX - Input::lastCursorPosX, Input::lastCursorPosY - Input::cursorPosY);
		Input::lastCursorPosX = Input::cursorPosX;
		Input::lastCursorPosY = Input::cursorPosY;
	}

	void Camera::do_mouse(double xOffSet, double yOffSet)
	{
		xOffSet *= m_MouseSensitivity;
		yOffSet *= m_MouseSensitivity;

		m_Yaw += static_cast<float>(xOffSet);
		m_Pitch += static_cast<float>(yOffSet);

		if (m_Pitch > 89.0f)
			m_Pitch = 89.0f;
		if (m_Pitch < -89.0f)
			m_Pitch = -89.0f;
		updateVectors();
	}
} }