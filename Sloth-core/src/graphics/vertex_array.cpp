#include "vertex_array.h"

namespace sloth { namespace graphics {

	VertexArray::VertexArray()
	{
		glCreateVertexArrays(1, &m_VertexArrayID);
	}

	VertexArray::~VertexArray()
	{
		for (int i = 0; i < m_Buffers.size(); ++i)
			delete m_Buffers[i];
	}

	void VertexArray::addBuffer(Buffer * buffer, GLuint index)
	{
		m_Buffers.push_back(buffer);
		glEnableVertexArrayAttrib(m_VertexArrayID, index);
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