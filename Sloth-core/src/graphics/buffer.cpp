#include "buffer.h"
namespace sloth { namespace graphics {

		Buffer::Buffer(GLfloat * data, GLsizei count, GLuint componentCount)
		{
			glCreateBuffers(1, &m_BufferID);
			glNamedBufferStorage(m_BufferID, count * sizeof(GL_FLOAT), data, GL_DYNAMIC_STORAGE_BIT);
			m_ComponentCount = componentCount;
		}

		void Buffer::bind() const
		{
			glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
		}

		void Buffer::unbind() const
		{
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}
} }
