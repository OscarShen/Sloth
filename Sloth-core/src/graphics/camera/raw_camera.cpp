#include "raw_camera.h"

namespace sloth { namespace graphics {

	glm::mat4 RawCamera::getViewMatrix() const
	{
		return glm::lookAt(m_Position, m_Position + m_Front, m_Up);
	}

	void RawCamera::updateVectors()
	{
		glm::vec3 front;
		float a = glm::cos(glm::radians(m_Pitch));
		front.x = a * glm::cos(glm::radians(m_Yaw));
		front.y = sin(glm::radians(m_Pitch));
		front.z = a * glm::sin(glm::radians(m_Yaw));
		m_Front = glm::normalize(front);
		m_Right = glm::normalize(glm::cross(m_Front, m_Up));
	}

} }

