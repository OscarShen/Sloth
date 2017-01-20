#pragma once

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include "../setup/macro.h"

namespace sloth { namespace graphics {

	enum CameraMovement
	{
		MOVEFORWARD,
		MOVEBACKWARD,
		MOVELEFT,
		MOVERIGHT
	};

	class Camera {
	private:
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
		Camera();

		void do_movement(CameraMovement direction, float deltatime);

		void do_mouse(double xOffSet, double yOffSet);

		glm::mat4 getViewMatrix() const;

		void updateVectors();

		inline glm::vec3 getPosition() const { return m_Position; }
	};

} }