#include "index_buffer.h"
namespace sloth { namespace graphics {

		IndexBuffer::IndexBuffer(GLushort * data, GLsizei count)
		{
			glCreateBuffers(1, &m_BufferID);
			glNamedBufferStorage(m_BufferID, count * sizeof(GLushort), data, GL_DYNAMIC_STORAGE_BIT);
			m_Count = count;
		}

		void IndexBuffer::bind() const
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID);
		}

		void IndexBuffer::unbind() const
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}
} }
