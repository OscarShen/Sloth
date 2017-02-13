#pragma once
#ifndef SLOTH_ENTITY_H_
#define SLOTH_ENTITY_H_

#include "../model/textured_model.hpp"
#include "../texture/texture_2d.h"

#include <glm/glm.hpp>
namespace sloth { namespace graphics {

	class Entity
	{
	protected:
		TexturedModel m_Model;
		glm::vec3 m_Position;
		float m_RotX, m_RotY, m_RotZ;
		float m_Scale;

		// ��¼ʹ�� atlases ����һ������
		int m_TextureIndex = 0;

	public:
		constexpr Entity(
			const TexturedModel &model,
			const glm::vec3 &position,
			const float rotX, const float rotY, const float rotZ,
			float scale
		) : m_Model(model), m_Position(position), m_RotX(rotX), m_RotY(rotY), 
			m_RotZ(rotZ), m_Scale(scale) {}

		constexpr Entity(
			const TexturedModel &model,
			const glm::vec3 &position,
			int textureIndex,
			const float rotX, const float rotY, const float rotZ,
			float scale
		) : m_Model(model), m_Position(position), m_TextureIndex(textureIndex), m_RotX(rotX), m_RotY(rotY),
			m_RotZ(rotZ), m_Scale(scale) {}


		inline TexturedModel getTexturedModel() const { return m_Model; }
		inline glm::vec3 getPosition() const { return m_Position; }
		inline float getRotX() const { return m_RotX; }
		inline float getRotY() const { return m_RotY; }
		inline float getRotZ() const { return m_RotZ; }
		inline float getScale() const { return m_Scale; }

		void setPosition(const glm::vec3 &position) { m_Position = position; }

		void increaseRotation(float dx, float dy, float dz);
		void increasePosition(float dx, float dy, float dz);

		float getTextureXOffset();
		float getTextureYOffset();

	};

} }


#endif // !SLOTH_ENTITY_H_
