#pragma once
#ifndef SLOTH_PLAYER_H_
#define SLOTH_PLAYER_H_
#include "entity.h"
#include "../setup/macro.h"
#include "../info/info.h"
#include "../../utils/timer.h"

namespace sloth { namespace graphics {

	class Player : public Entity
	{
	private:
		float m_CurrentSpeed = 0.0f;
		float m_CurrentTurnSpeed = 0.0f;
		float m_UpwardSpeed = 0.0f;
		bool m_IsInAir = false;

	public:
		constexpr Player(
			const TexturedModel &model,
			const glm::vec3 &position,
			const float rotX, const float rotY, const float rotZ,
			float scale
		) :Entity(model, position, rotX, rotY, rotZ, scale) {}

		void move();
		void jump();

	private:
		void checkInputs();
	};

} }



#endif // !SLOTH_PLAYER_H_
