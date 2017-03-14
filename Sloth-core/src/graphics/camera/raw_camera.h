#pragma once
#ifndef SLOTH_RAW_CAMERA_H_
#define SLOTH_RAW_CAMERA_H_

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include "../window.h"
#include "../../config/header.hpp"

namespace sloth { namespace graphics {

	class RawCamera
	{
	protected:
		// vectors of camera
		glm::vec3 m_Position;

		float m_Pitch;
		float m_Yaw;

	public:
		RawCamera()
			:m_Position(CAMERA_INIT_POS), 
			m_Pitch(CAMERA_INIT_PITCH), m_Yaw(CAMERA_INIT_YAW)  {}
		virtual ~RawCamera() {}

		virtual void process(SlothWindow * window) = 0;

		virtual glm::mat4 getViewMatrix() const = 0;

		virtual glm::vec3 getFront() const = 0;

		inline glm::vec3 getPosition() const { return m_Position; }
		inline float getPitch() const { return m_Pitch; }
		inline float getYaw() const { return m_Yaw; }

		void setPosition(const glm::vec3 &position) { m_Position = position; }
	};

} }


#endif // !SLOTH_RAW_CAMERA_H_
