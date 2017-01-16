#pragma once
#ifndef SLOTH_INDEXBUFFER_H_
#define SLOTH_INDEXBUFFER_H_

#include <GL/glew.h>

namespace sloth { namespace graphics {

		class IndexBuffer {
		private:
			unsigned int m_BufferID;
			int m_Count;

		public:
			IndexBuffer(unsigned short *data, int count);
			IndexBuffer(unsigned int *data, int count);
			~IndexBuffer();
			inline int getCount() const { return m_Count; }
			inline unsigned int getID() const { return m_BufferID; }
			void bind() const;
			void unbind() const;
		};

} }

#endif // !SLOTH_INDEXBUFFER_H_
