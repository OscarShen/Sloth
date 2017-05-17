#include "shadow_box.h"
#include <config/header.hpp>
#include <camera/raw_camera.h>
namespace sloth {
	const float ShadowBox::OFFSET = 10.0f;
	const glm::vec4 ShadowBox::UP = glm::vec4(0.0f, 1.0f, 0.0f, 0.0f);
	const glm::vec4 ShadowBox::FORWARD = glm::vec4(0.0f, 0.0f, -1.0f, 0.0f);
	const float ShadowBox::SHADOW_DISTANCE = 100.0f;
	ShadowBox::ShadowBox(const glm::mat4 & lightView, RawCamera & camera)
		:m_LightView(lightView), m_Camera(camera)
	{
	}

	void ShadowBox::update()
	{

	}

	void ShadowBox::calculateWidthAndHeight()
	{
		m_FarHeight = SHADOW_DISTANCE * std::tan(glm::radians(PERSPECTIVE_FOV));
		m_NearHeight = PERSPECTIVE_NEAR_PLANE * std::tan(glm::radians(PERSPECTIVE_FOV));
		float aspectRatio = SCREEN_WIDTH / SCREEN_HEIGHT;
		m_FarWidth = m_FarHeight * aspectRatio;
		m_NearWidth = m_NearHeight * aspectRatio;
	}

	glm::mat4 ShadowBox::calculateCameraRotation()
	{
		glm::mat4 rotate = glm::rotate(glm::mat4(), glm::radians(m_Camera.getYaw()), glm::vec3(0.0f, 1.0f, 0.0f));
		return glm::mat4();
	}

} 
