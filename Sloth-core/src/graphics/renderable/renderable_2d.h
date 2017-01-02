#pragma once
#ifndef SLOTH_RENDERER_2D_H_
#define SLOTH_RENDERER_2D_H_

#include <glm/glm.hpp>
#include "../renderer/renderer_2d.h"
#include "../buffers/buffer.h"
#include "../buffers/index_buffer.h"
#include "../buffers/vertex_array.h"
#include "../shader/shader_manager.h"

namespace sloth { namespace graphics {
	class Renderer2D;

	class Renderable2D
	{
	protected:
		VertexArray *m_VAO;
		IndexBuffer *m_IBO;
		unsigned int m_Shader;

	public:
		Renderable2D(const unsigned int shader) :m_Shader(shader) {}
		virtual ~Renderable2D();

		virtual void submitToRenderer(Renderer2D* renderer) const;
		virtual void attachBuffer(unsigned int index, float *data, int count, unsigned int componentCount);
		virtual void detachBuffer(unsigned int index);

		inline const VertexArray* getVAO() const { return m_VAO; }
		inline const IndexBuffer* getIBO() const { return m_IBO; }
		inline const unsigned int getShader() const { return m_Shader; }
	};

} }

#endif // !SLOTH_RENDERER_2D_H_
