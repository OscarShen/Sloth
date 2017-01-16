#include "vertex_array.h"

namespace sloth { namespace graphics {

	VertexArray::VertexArray()
	{
		glCreateVertexArrays(1, &m_VertexArrayID);
	}

	VertexArray::~VertexArray()
	{
		auto i = m_Buffers.begin();
		while (i != m_Buffers.end())
		{
			auto j = i;
			++i;
			delete m_Buffers[j->first];
			m_Buffers.erase(j->first);
		}
		delete m_ElementBuffer;
		glDeleteVertexArrays(1, &m_VertexArrayID);
	}

	void VertexArray::addBuffer(Buffer * buffer, unsigned int index)
	{
		if (m_Buffers.find(index) != m_Buffers.end())
		{
			delete m_Buffers[index];
		}
		glEnableVertexArrayAttrib(m_VertexArrayID, index);
		glVertexArrayVertexBuffer(m_VertexArrayID, index, buffer->getBufferID(), 0, buffer->getComponentCount() * sizeof(GLfloat));
		glVertexArrayAttribFormat(m_VertexArrayID, index, buffer->getComponentCount(), GL_FLOAT, GL_FALSE, 0);
		m_Buffers[index] = buffer;
	}

	void VertexArray::addElementBuffer(IndexBuffer * buffer)
	{
		glVertexArrayElementBuffer(m_VertexArrayID, buffer->getID());
		m_ElementBuffer = buffer;
	}

	void VertexArray::deleteBuffer(unsigned int index)
	{
		if (m_Buffers.find(index) != m_Buffers.end())
		{
			delete m_Buffers[index];
			m_Buffers.erase(index);
		}
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