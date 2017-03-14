#pragma once
#ifndef SLOTH_CAMERA_3RD_H_
#define SLOTH_CAMERA_3RD_H_

#include "raw_camera.h"
#include "../entities/player.h"

namespace sloth { namespace graphics {

	class Camera3rd : public RawCamera
	{
	protected:
		float m_DistanceFromPlayer = 50.0f;
		float m_AngleAroundPlayer = 0.0f;
		Player &m_Player;

	private:
		// ¼ÇÂ¼Ä³Ò»Ê±¿Ì
		double m_ScrollRecord = 0.0;
		double m_CursorCurrentPosX = 0.0, m_CursorCurrentPosY = 0.0;
		double m_CursorLastPosX = 0.0, m_CursorLastPosY = 0.0;
		bool m_FirstMove = true;

	public:
		Camera3rd(Player &player);
		virtual ~Camera3rd() {}

		virtual void process(SlothWindow * window) override;
		virtual glm::mat4 getViewMatrix() const override;
		virtual glm::vec3 getFront() const override { return m_Player.getPosition() - m_Position; }

	private:
		void calculateZoom(double yOffset);
		void calculatePitch(double deltaDistanceY);
		void calculateAngleAroundPlayer(double deltaDistanceX);
		inline float calculateHorizontalDistance() { return m_DistanceFromPlayer * glm::cos(glm::radians(m_Pitch)); }
		inline float calculateVerticalDistance() { return m_DistanceFromPlayer * glm::sin(glm::radians(m_Pitch)); }
		void calculateCameraPosition(float horizDistance, float verticDistance);
	};

} }

#endif // !SLOTH_CAMERA_3RD_H_
