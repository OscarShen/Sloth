#include "static_sprite.h"
namespace sloth { namespace graphics {

		StaticSprite::StaticSprite(float x, float y, float width, float height, glm::vec4 &color, Shader &shader)
			:Renderable2D(glm::vec3(x,y,0.0f),glm::vec2(width,height),color),m_Shader(shader)
		{
			m_VertexArray = new VertexArray();
			GLfloat vertices[] =
			{
				0, 0, 0,
				0,height,0,
				width,height,0,
				width,0,0
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
	}
}
