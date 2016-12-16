#include "batch_renderer_2d.h"
#include "../utils/error_check.h"
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

		unsigned int r = static_cast<unsigned int>(color.r * 255.0f);
		unsigned int g = static_cast<unsigned int>(color.g * 255.0f);
		unsigned int b = static_cast<unsigned int>(color.b * 255.0f);
		unsigned int a = static_cast<unsigned int>(color.a * 255.0f);

		unsigned int c = a << 24 | b << 16 | g << 8 | r;

		m_Buffer->vertex = *m_TransformationBack * glm::vec4(position, 1.0f);
		m_Buffer->color = c;
		m_Buffer++;

		m_Buffer->vertex = *m_TransformationBack * glm::vec4(position.x, position.y + size.y, position.z, 1.0f);
		m_Buffer->color = c;
		m_Buffer++;

		m_Buffer->vertex = *m_TransformationBack * glm::vec4(position.x + size.x, position.y + size.y, position.z,1.0f);
		m_Buffer->color = c;
		m_Buffer++;

		m_Buffer->vertex = *m_TransformationBack * glm::vec4(position.x + size.x, position.y, position.z, 1.0f);
		m_Buffer->color = c;
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
		glVertexArrayAttribFormat(m_VAO, SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, 0);
		glVertexArrayVertexBuffer(m_VAO, SHADER_COLOR_INDEX, m_VBO, 3 * sizeof(GLfloat), RENDERER_VERTEX_SIZE);
		glVertexArrayAttribFormat(m_VAO, SHADER_COLOR_INDEX, 4, GL_UNSIGNED_BYTE, GL_TRUE, 0);

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