#pragma once
#ifndef SLOTH_STATIC_SPRITE_H_
#define SLOTH_STATIC_SPRITE_H_

#include "renderable_2d.h"

namespace sloth { namespace graphics {

		class StaticSprite : public Renderable2D
		{
		private:
			VertexArray *m_VertexArray;
			IndexBuffer *m_IndexBuffer;
			Shader &m_Shader;

		public:
			StaticSprite(float x, float y, float width, float height, glm::vec4 &color, Shader &shader);


			inline const VertexArray* getVAO() const { return m_VertexArray; }
			inline const IndexBuffer* getIBO() const { return m_IndexBuffer; }
			inline Shader& getShader() const { return m_Shader; }

		};
} }

#endif // !SLOTH_STATIC_SPRITE_H_
