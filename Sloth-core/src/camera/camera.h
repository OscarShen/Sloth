#pragma once
#ifndef SLOTH_CAMERA_H_
#define SLOTH_CAMERA_H_

#include <sloth.h>
#include <info/info.h>
#include <utils/timer.h>
#include "raw_camera.h"

namespace sloth {

	enum CameraMovement
	{
		MOVEFORWARD,
		MOVEBACKWARD,
		MOVELEFT,
		MOVERIGHT
	};
	class SlothWindow;
	class Camera : public RawCamera
	{
	private:
		glm::vec3 m_Up;
		glm::vec3 m_Right;
		glm::vec3 m_Front;
		float m_MouseSensitivity;
		float m_MoveSpeed;

		bool firstMouse;
	public:
		Camera() : RawCamera(), m_Up(CAMERA_INIT_UP), m_Right(CAMERA_INIT_RIGHT), m_Front(CAMERA_INIT_FRONT),
			m_MoveSpeed(MOVE_SPEED), m_MouseSensitivity(MOUSE_SENSITIVITY), firstMouse(true) {}

		virtual ~Camera() {}

		virtual void process(SlothWindow * window) override;

		virtual glm::mat4 getViewMatrix() const override;

		virtual glm::vec3 getFront() const override { return m_Front; }

		void invertPitch();

	private:
		void process_keyboard(SlothWindow * window);

		void do_movement(CameraMovement direction, float deltaTime);

		void process_mouse(SlothWindow * window);

		void do_mouse(double xOffSet, double yOffSet);

		void updateVectors();
	};

}

#endif // !SLOTH_CAMERA_H_
