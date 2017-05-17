#pragma once
#ifndef SLOTH_ENTITY_H_
#define SLOTH_ENTITY_H_

#include <sloth.h>
#include <model/textured_model.hpp>

namespace sloth {

	class Entity
	{
	protected:
		TexturedModel m_Model;
		glm::vec3 m_Position;
		float m_RotX, m_RotY, m_RotZ;
		float m_Scale;

		// 记录使用 atlases 中哪一个纹理
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

		float getTextureXOffset() const;
		float getTextureYOffset() const;

	};

}


#endif // !SLOTH_ENTITY_H_
