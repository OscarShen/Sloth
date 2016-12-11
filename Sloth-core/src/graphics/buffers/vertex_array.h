#pragma once
#ifndef SLOTH_VERTEX_ARRAY_H_
#define SLOTH_VERTEX_ARRAY_H_

#include "buffer.h"
#include <GL/glew.h>
#include <vector>
namespace sloth { namespace graphics {

	class VertexArray
	{
	private:
		GLuint m_VertexArrayID;
		std::vector<Buffer*> m_Buffers;

	public:
		VertexArray();
		~VertexArray();
		void addBuffer(Buffer *buffer, GLuint index);
		void bind() const;
		void unbind() const;
	};


} }



#endif // !SLOTH_VERTEX_ARRAY_H_
