#pragma once
#ifndef SLOTH_RENDERABLE_H_
#define SLOTH_RENDERABLE_H_

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "buffers/buffer.h"
#include "buffers/index_buffer.h"
#include "buffers/vertex_array.h"
#include "shader.h"

namespace sloth { namespace graphics {

	class Renderable2D
	{
	protected:
		glm::vec3 m_Position;
		glm::vec2 m_Size;
		glm::vec4 m_Color;

		Shader *m_Shader;
		VertexArray *m_VertexArray;
		IndexBuffer *m_IndexBuffer;

	public:
		Renderable2D(const glm::vec3 &position, const glm::vec2 &size, const glm::vec4 &color, Shader *shader)
			:m_Position(position), m_Size(size), m_Color(color), m_Shader(shader)
		{
			m_VertexArray = new VertexArray();
			GLfloat vertices[] =
			{
				0, 0, 0,
				0,size.y,0,
				size.x,size.y,0,
				size.x,0,0
			};
			GLfloat colors[] =
			{
				color.r,color.g,color.b,color.a,
				color.r,color.g,color.b,color.a,
				color.r,color.g,color.b,color.a,
				color.r,color.g,color.b,color.a
			};

			m_VertexArray->addBuffer(new Buffer(vertices, 4 * 3, 3), 0);
			m_VertexArray->addBuffer(new Buffer(colors, 4 * 4, 4), 1);


			GLushort indices[] = { 0, 1, 2, 2, 3, 0 };
			m_IndexBuffer = new IndexBuffer(indices, 6);
		}

		virtual ~Renderable2D()
		{
			delete m_VertexArray;
			delete m_IndexBuffer;
		}

		inline const VertexArray* getVAO() const { return m_VertexArray; }
		inline const IndexBuffer* getIBO() const { return m_IndexBuffer; }
		inline Shader* getShader() const { return m_Shader; }

		inline const glm::vec3& getPosition()const { return m_Position; }
		inline const glm::vec2& getSize()const { return m_Size; }
		inline const glm::vec4& getColor()const { return m_Color; }
	};

} }

#endif // !SLOTH_RENDERABLE_H_
