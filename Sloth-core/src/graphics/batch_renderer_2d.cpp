#include "batch_renderer_2d.h"
namespace sloth { namespace graphics {
	BatchRenderer2D::BatchRenderer2D()
	{
		init();
	}

	BatchRenderer2D::~BatchRenderer2D()
	{
		delete m_IBO;
		glDeleteBuffers(1, &m_VBO);
	}

	void BatchRenderer2D::begin()
	{
		m_Buffer = (VertexData*) glMapNamedBuffer(m_VBO, GL_WRITE_ONLY);
	}

	void sloth::graphics::BatchRenderer2D::sumbit(const Renderable2D * renderable)
	{
		const glm::vec3 &position = renderable->getPosition();
		const glm::vec2 &size = renderable->getSize();
		const glm::vec4 &color = renderable->getColor();

		m_Buffer->vertex = position;
		m_Buffer->color = color;
		m_Buffer++;

		m_Buffer->vertex = glm::vec3(position.x, position.y + size.y, position.z);
		m_Buffer->color = color;
		m_Buffer++;

		m_Buffer->vertex = glm::vec3(position.x + size.x, position.y + size.y, position.z);
		m_Buffer->color = color;
		m_Buffer++;

		m_Buffer->vertex = glm::vec3(position.x + size.x, position.y, position.z);
		m_Buffer->color = color;
		m_Buffer++;

		m_IndexCount += 6;
	}

	void BatchRenderer2D::end()
	{
		glUnmapNamedBuffer(m_VBO);
	}

	void BatchRenderer2D::flush()
	{
		glBindVertexArray(m_VAO);
		m_IBO->bind();
		glDrawElements(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_INT, nullptr);
		m_IBO->unbind();
		glBindVertexArray(0);
	}

	void BatchRenderer2D::init()
	{
		glCreateVertexArrays(1, &m_VAO);
		glCreateBuffers(1, &m_VBO);
		glNamedBufferData(m_VBO, RENDERER_BUFFER_SIZE, nullptr, GL_DYNAMIC_DRAW);
		glEnableVertexArrayAttrib(m_VAO, SHADER_VERTEX_INDEX);
		glEnableVertexArrayAttrib(m_VAO, SHADER_COLOR_INDEX);
		glVertexArrayVertexBuffer(m_VAO, SHADER_VERTEX_INDEX, m_VBO, 0, RENDERER_VERTEX_SIZE);
		glVertexAttribFormat(SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, 0);
		glVertexArrayVertexBuffer(m_VAO, SHADER_COLOR_INDEX, m_VBO, 3 * sizeof(GLfloat), RENDERER_VERTEX_SIZE);
		glVertexAttribFormat(SHADER_COLOR_INDEX, 4, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT));

		GLuint *indices = new GLuint[RENDERER_INDICES_SIZE];
		int offset = 0;
		for (int i = 0; i < RENDERER_INDICES_SIZE; i += 6)
		{
			indices[i] = offset;
			indices[i + 1] = offset + 1;
			indices[i + 2] = offset + 2;

			indices[i + 3] = offset + 2;
			indices[i + 4] = offset + 3;
			indices[i + 5] = offset + 0;

			offset += 4; // six vertex storage in four elements
		}
		m_IBO = new IndexBuffer(indices, RENDERER_INDICES_SIZE);
		delete[] indices;
	}

} }