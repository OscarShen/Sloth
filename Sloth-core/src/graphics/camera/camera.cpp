#include "camera.h"

namespace sloth { namespace graphics {

	Camera::Camera()
		:m_Position(CAMERA_INIT_POS), m_Up(CAMERA_INIT_UP), m_Right(CAMERA_INIT_RIGHT), m_Front(CAMERA_INIT_FRONT), m_MoveSpeed(MOVE_SPEED),
		m_Pitch(CAMERA_INIT_PITCH), m_Yaw(CAMERA_INIT_YAW), m_MouseSensitivity(MOUSE_SENSITIVITY), firstMouse(true) {}

	void Camera::do_movement(CameraMovement direction, float deltatime)
	{
		float v = deltatime * m_MoveSpeed;
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

	glm::mat4 Camera::getViewMatrix() const
	{
		return glm::lookAt(m_Position, m_Position + m_Front, m_Up);
	}

	void Camera::updateVectors()
	{
		glm::vec3 front;
		float a = cos(glm::radians(m_Pitch));
		front.x = a * cos(glm::radians(m_Yaw));
		front.y = sin(glm::radians(m_Pitch));
		front.z = a * sin(glm::radians(m_Yaw));
		m_Front = glm::normalize(front);
		m_Right = glm::normalize(glm::cross(m_Front, m_Up));
	}

} }