#pragma once
#ifndef SLOTH_BUFFER_H_
#define SLOTH_BUFFER_H_

#include <sloth.h>
#include <config/header.hpp>

namespace sloth {

	class Buffer
	{
	private:
		unsigned int m_BufferID;
		unsigned int m_ComponentCount;

	public:
		Buffer(float *data, unsigned int count, unsigned int componentCount);
		~Buffer();
		inline unsigned int getComponentCount() const { return m_ComponentCount; }
		void bind() const;
		void unbind() const;
		unsigned int getBufferID() const { return m_BufferID; }
	};
}

#endif // !SLOTH_BUFFER_H_
