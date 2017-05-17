#include "buffer.h"
namespace sloth {

		Buffer::Buffer(float * data, unsigned int count, unsigned int componentCount)
		{
			glCreateBuffers(1, &m_BufferID);
			glNamedBufferStorage(m_BufferID, count * sizeof(GLfloat), data, GL_DYNAMIC_STORAGE_BIT);
			m_ComponentCount = componentCount;
		}

		Buffer::~Buffer()
		{
			glDeleteBuffers(1, &m_BufferID);
		}

		void Buffer::bind() const
		{
			glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
		}

		void Buffer::unbind() const
		{
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}
}
