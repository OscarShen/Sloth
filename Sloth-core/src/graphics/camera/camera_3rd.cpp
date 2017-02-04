#include "camera_3rd.h"
#include <iostream>

namespace sloth { namespace graphics {

	Camera3rd::Camera3rd(Player & player)
		:RawCamera(), m_Player(player)
	{
	}

	void Camera3rd::process(SlothWindow * window)
	{
		glfwGetCursorPos(window->getGLFWwindow(), &m_CursorCurrentPosX, &m_CursorCurrentPosY);
		if (m_FirstMove) {
			m_CursorLastPosX = m_CursorCurrentPosX;
			m_CursorLastPosY = m_CursorCurrentPosY;
			m_FirstMove = false;
		}
		calculateZoom(m_ScrollRecord - Input::scrollY);
		m_ScrollRecord = Input::scrollY;
		// GLFW 鼠标不会返回 action = RELEASE, 故而只能使用get函数来获取当前状态
		if (glfwGetMouseButton(window->getGLFWwindow(), GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
			calculateAngleAroundPlayer(m_CursorCurrentPosX - m_CursorLastPosX);
			calculatePitch(m_CursorCurrentPosY - m_CursorLastPosY);
		}
		float horizontalDistance = calculateHorizontalDistance();
		float verticalDistance = calculateVerticalDistance();
		calculateCameraPosition(horizontalDistance, verticalDistance);
		
		m_Yaw = 180.0f - (m_Player.getRotY() + m_AngleAroundPlayer);
		m_CursorLastPosX = m_CursorCurrentPosX;
		m_CursorLastPosY = m_CursorCurrentPosY;
	}

	glm::mat4 Camera3rd::getViewMatrix() const
	{
		return glm::lookAt(m_Position, m_Player.getPosition(), glm::vec3(0.0f, 1.0f, 0.0f));
	}

	void Camera3rd::calculateZoom(double yOffset)
	{
		float zoomLevel = static_cast<float>(yOffset);
		m_DistanceFromPlayer -= zoomLevel;
	}

	void Camera3rd::calculatePitch(double deltaDistanceY)
	{
		float pitchChange = static_cast<float>(deltaDistanceY) * 0.1f;
		m_Pitch -= pitchChange;
	}

	void Camera3rd::calculateAngleAroundPlayer(double deltaDistanceX)
	{
		float angleChange = static_cast<float>(deltaDistanceX) * 0.3f;
		m_AngleAroundPlayer -= angleChange;
	}

	void Camera3rd::calculateCameraPosition(float horizDistance, float verticDistance)
	{
		float theta = m_Player.getRotY() + m_AngleAroundPlayer;
		float offsetX = horizDistance * glm::sin(glm::radians(theta));
		float offsetZ = horizDistance * glm::cos(glm::radians(theta));
		m_Position.x = m_Player.getPosition().x - offsetX;
		m_Position.z = m_Player.getPosition().z - offsetZ;
		m_Position.y = m_Player.getPosition().y + verticDistance;
	}


} }
