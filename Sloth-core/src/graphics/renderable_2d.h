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

	struct VertexData
	{
		glm::vec3 vertex;
		glm::vec4 color;
	};

	class Renderable2D
	{
	protected:
		glm::vec3 m_Position;
		glm::vec2 m_Size;
		glm::vec4 m_Color;

	public:
		Renderable2D(const glm::vec3 &position, const glm::vec2 &size, const glm::vec4 &color)
			:m_Position(position), m_Size(size), m_Color(color) 
		{
		}

		virtual ~Renderable2D()
		{
		}

		inline const glm::vec3& getPosition()const { return m_Position; }
		inline const glm::vec2& getSize()const { return m_Size; }
		inline const glm::vec4& getColor()const { return m_Color; }
	};

} }

#endif // !SLOTH_RENDERABLE_H_
