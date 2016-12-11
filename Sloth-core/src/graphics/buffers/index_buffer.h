#pragma once
#ifndef SLOTH_INDEXBUFFER_H_
#define SLOTH_INDEXBUFFER_H_

#include <GL/glew.h>

namespace sloth { namespace graphics {

		class IndexBuffer {
		private:
			GLuint m_BufferID;
			GLsizei m_Count;

		public:
			IndexBuffer(GLushort *data, GLsizei count);
			inline GLsizei getCount() const { return m_Count; }
			void bind() const;
			void unbind() const;
		};

} }

#endif // !SLOTH_INDEXBUFFER_H_
