#include "buffer.h"
#include "../../utils/error_check.h"
namespace sloth { namespace graphics {

		Buffer::Buffer(GLfloat * data, GLsizei count, GLuint componentCount)
		{
			glCreateBuffers(1, &m_BufferID);
glCheckError();
			glNamedBufferStorage(m_BufferID, count * sizeof(GLfloat), data, GL_DYNAMIC_STORAGE_BIT);
glCheckError();
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
} }
