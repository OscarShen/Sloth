#pragma once
#ifndef SLOTH_VERTEX_ARRAY_H_
#define SLOTH_VERTEX_ARRAY_H_

#include "buffer.h"
#include "index_buffer.h"
#include <GL/glew.h>
#include <map>
namespace sloth { namespace graphics {

	class VertexArray
	{
	private:
		unsigned int m_VertexArrayID;
		std::map<unsigned int, Buffer*> m_Buffers;
		IndexBuffer* m_ElementBuffer;

	public:
		VertexArray();
		~VertexArray();
		void addBuffer(Buffer *buffer, unsigned int index);
		void addElementBuffer(IndexBuffer *buffer);
		void deleteBuffer(unsigned int index);
		void bind() const;
		void unbind() const;

		inline unsigned int getVaoID() const { return m_VertexArrayID; }
	};


} }



#endif // !SLOTH_VERTEX_ARRAY_H_
