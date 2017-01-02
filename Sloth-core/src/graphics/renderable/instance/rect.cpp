#include "rect.h"

namespace sloth { namespace graphics {
	Rectangle::Rectangle(unsigned int shader)
		:Renderable2D(shader)
	{
		constr(0.0f, 1.0f, 1.0f, 1.0f, shader);
	}
	Rectangle::Rectangle(float x, float y, float width, float height, unsigned int shader)
		:Renderable2D(shader)
	{
		constr(x, y, width, height, shader);
	}

	Rectangle::~Rectangle()
	{
		delete m_VAO;
		delete m_IBO;
	}
	void Rectangle::constr(float x, float y, float width, float height, unsigned int shader)
	{
		m_VAO = new VertexArray();
		float x1 = x + width, y1 = y - height;
		GLfloat vertices[] =
		{
			x, y1, 0,
			x1,y1, 0,
			x,  y, 0,
			x1, y, 0
		};
		m_VAO->addBuffer(new Buffer(vertices, 4 * 3, 3), 0);

		GLushort indices[] = { 0,1,2,2,1,3 };
		m_IBO = new IndexBuffer(indices, 6);
	}
} }
