#pragma once
#ifndef SLOTH_RAW_CAMERA_H_
#define SLOTH_RAW_CAMERA_H_

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include "../setup/macro.h"
#include "../window.h"

namespace sloth { namespace graphics {

	class SlothWindow;
	class RawCamera
	{
	protected:
		// vectors of camera
		glm::vec3 m_Position;
		glm::vec3 m_Up;
		glm::vec3 m_Right;
		glm::vec3 m_Front;

		float m_Pitch;
		float m_Yaw;

		float m_MouseSensitivity;
		float m_MoveSpeed;

	public:
		bool firstMouse;

	public:
		RawCamera()
			:m_Position(CAMERA_INIT_POS), m_Up(CAMERA_INIT_UP), m_Right(CAMERA_INIT_RIGHT), m_Front(CAMERA_INIT_FRONT), m_MoveSpeed(MOVE_SPEED),
			m_Pitch(CAMERA_INIT_PITCH), m_Yaw(CAMERA_INIT_YAW), m_MouseSensitivity(MOUSE_SENSITIVITY), firstMouse(true) {}
		virtual ~RawCamera() {}

		virtual void process(SlothWindow * window) = 0;

		virtual glm::mat4 getViewMatrix() const;

		virtual void updateVectors();

		virtual inline glm::vec3 getPosition() const { return m_Position; }
	};

} }


#endif // !SLOTH_RAW_CAMERA_H_
