#pragma once
#ifndef SLOTH_BUFFER_H_
#define SLOTH_BUFFER_H_

#include <GL/glew.h>

namespace sloth { namespace graphics {

	class Buffer
	{
	private:
		GLuint m_BufferID;
		GLuint m_ComponentCount;

	public:
		Buffer(GLfloat *data, GLsizei count, GLuint componentCount);
		inline GLuint getComponentCount() const { return m_ComponentCount; }
		void bind() const;
		void unbind() const;
		GLuint getBufferID() const { return m_BufferID; }
	};

} }

#endif // !SLOTH_BUFFER_H_
