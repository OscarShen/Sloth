#include "vertex_array.h"

namespace sloth { namespace graphics {

	VertexArray::VertexArray()
	{
		glCreateVertexArrays(1, &m_VertexArrayID);
	}

	VertexArray::~VertexArray()
	{
		for (size_t i = 0; i < m_Buffers.size(); ++i)
		{
			delete m_Buffers[i];
		}
		glDeleteVertexArrays(1, &m_VertexArrayID);
	}

	void VertexArray::addBuffer(Buffer * buffer, GLuint index)
	{
		m_Buffers.push_back(buffer);
		glEnableVertexArrayAttrib(m_VertexArrayID, index);
		glVertexArrayVertexBuffer(m_VertexArrayID, index, buffer->getBufferID(), 0, buffer->getComponentCount() * sizeof(GL_FLAT));
		glVertexArrayAttribFormat(m_VertexArrayID, index, buffer->getComponentCount(), GL_FLOAT, GL_FALSE, 0);
	}

	void VertexArray::bind() const
	{
		glBindVertexArray(m_VertexArrayID);
	}

	void VertexArray::unbind() const
	{
		glBindVertexArray(0);
	}

} }