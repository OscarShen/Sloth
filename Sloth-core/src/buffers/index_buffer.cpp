#include "index_buffer.h"
namespace sloth {

		IndexBuffer::IndexBuffer(unsigned short * data, int count)
		{
			glCreateBuffers(1, &m_BufferID);
			glNamedBufferStorage(m_BufferID, count * sizeof(unsigned short), data, GL_DYNAMIC_STORAGE_BIT);
			m_Count = count;
		}

		IndexBuffer::IndexBuffer(unsigned int * data, int count)
		{
			glCreateBuffers(1, &m_BufferID);
			glNamedBufferStorage(m_BufferID, count * sizeof(unsigned int), data, GL_DYNAMIC_STORAGE_BIT);
			m_Count = count;
		}

		IndexBuffer::~IndexBuffer()
		{
			glDeleteBuffers(1, &m_BufferID);
		}

		void IndexBuffer::bind() const
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID);
		}

		void IndexBuffer::unbind() const
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}
}
