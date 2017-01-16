#pragma once

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\quaternion.hpp>

#define CAMERA_INIT_POS		glm::vec3(0.0f,5.0f,10.0f)
#define CAMERA_INIT_UP		glm::vec3(0.0f,1.0f,0.0f)
#define CAMERA_INIT_FRONT	glm::vec3(0.0f,0.0f,-1.0f)
#define CAMERA_INIT_RIGHT	glm::normalize(glm::cross(CAMERA_INIT_UP, CAMERA_INIT_POS + CAMERA_INIT_FRONT))
#define CAMERA_INIT_PITCH	0.0f
#define CAMERA_INIT_YAW		-90.0f
#define MOUSE_SENSITIVITY	2.0f
#define MOVE_SPEED			5.0f

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