#include "player.h"

namespace sloth { namespace graphics {

	void Player::move()
	{
		checkInputs();
		float deltaFrameTime = static_cast<float>(util::Timer::deltaFrameTime);
		increaseRotation(0.0f, m_CurrentTurnSpeed * deltaFrameTime, 0.0f);
		float distance = m_CurrentSpeed * deltaFrameTime;
		float dx = distance * glm::sin(glm::radians(getRotY()));
		float dz = distance * glm::cos(glm::radians(getRotY()));
		increasePosition(dx, 0.0f, dz);
		m_UpwardSpeed += PLAYER_GRAVITY * deltaFrameTime;
		increasePosition(0.0f, m_UpwardSpeed * deltaFrameTime, 0.0f);
		if (m_Position.y < PLAYER_TERRAIN_HEIGHT) {
			m_UpwardSpeed = 0;
			m_Position.y = PLAYER_TERRAIN_HEIGHT;
			m_IsInAir = false;
		}
	}

	void Player::jump()
	{
		if (!m_IsInAir) {
			m_UpwardSpeed = PLAYER_JUMP_POWER;
			m_IsInAir = true;
		}
	}

	void Player::checkInputs()
	{
		if (Input::keys[GLFW_KEY_W]) {
			m_CurrentSpeed = PLAYER_RUN_SPEED;
		}
		else if (Input::keys[GLFW_KEY_S]) {
			m_CurrentSpeed = -PLAYER_RUN_SPEED;
		}
		else {
			m_CurrentSpeed = 0.0f;
		}

		if (Input::keys[GLFW_KEY_D]) {
			m_CurrentTurnSpeed = -PLAYER_TURN_SPEED;
		}
		else if (Input::keys[GLFW_KEY_A]) {
			m_CurrentTurnSpeed = PLAYER_TURN_SPEED;
		}
		else {
			m_CurrentTurnSpeed = 0.0f;
		}

		if (Input::keys[GLFW_KEY_SPACE]) {
			jump();
		}
	}

} }
