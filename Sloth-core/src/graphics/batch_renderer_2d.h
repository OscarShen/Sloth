#pragma once
#ifndef BATCH_RENDERER_2D_H_
#define BATCH_RENDERER_2D_H_

#include "renderer_2d.h"
#include "buffers/index_buffer.h"

#include <vector>

namespace sloth { namespace graphics {

#define RENDERER_MAX_SPRITES	10000
#define RENDERER_VERTEX_SIZE	sizeof(VertexData)
#define RENDERER_SPRITE_SIZE	RENDERER_VERTEX_SIZE * 4
#define RENDERER_BUFFER_SIZE	RENDERER_SPRITE_SIZE * RENDERER_MAX_SPRITES
#define RENDERER_INDICES_SIZE	RENDERER_MAX_SPRITES * 6

#define SHADER_VERTEX_INDEX		0
#define SHADER_COLOR_INDEX		1

	class BatchRenderer2D :public Renderer2D
	{
	private:
		GLuint m_VAO;
		IndexBuffer *m_IBO; // we can't have this, because ibo may be very large, i.e. 60000
		GLsizei m_IndexCount;
		GLuint m_VBO;
		VertexData *m_Buffer;

	public:
		BatchRenderer2D();
		~BatchRenderer2D();
		void begin();
		void sumbit(const Renderable2D *renderable) override;
		void end();
		void flush() override;

	private:
		void init();
	};

} }


#endif // !BATCH_RENDERER_2D_H_
