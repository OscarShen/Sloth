#pragma once
#ifndef SLOTH_ENTITY_H_
#define SLOTH_ENTITY_H_

#include "../model/textured_model.hpp"
#include "../texture/texture_2d.h"

#include <glm/glm.hpp>
namespace sloth { namespace graphics {

	class Entity
	{
	private:
		TexturedModel m_Model;
		glm::vec3 m_Position;
		float m_RotX, m_RotY, m_RotZ;
		float m_Scale;

	public:
		constexpr Entity(
			const TexturedModel &model,
			const glm::vec3 &position,
			const float rotX, const float rotY, const float rotZ,
			float scale
		) : m_Model(model), m_Position(position), m_RotX(rotX), m_RotY(rotY), 
			m_RotZ(rotZ), m_Scale(scale) {}


		inline TexturedModel getTexturedModel() const { return m_Model; }
		inline glm::vec3 getPosition() const { return m_Position; }
		inline float getRotX() const { return m_RotX; }
		inline float getRotY() const { return m_RotY; }
		inline float getRotZ() const { return m_RotZ; }
		inline float getScale() const { return m_Scale; }

		void increaseRotation(float dx, float dy, float dz);
		void increasePosition(float dx, float dy, float dz);
	};

} }


#endif // !SLOTH_ENTITY_H_
