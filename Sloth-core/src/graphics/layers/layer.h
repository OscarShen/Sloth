#pragma once
#ifndef SLOTH_LAYER_H_
#define SLOTH_LAYER_H_
#include "../renderable_2d.h"
#include "../renderer_2d.h"

#include <glm/glm.hpp>
#include <vector>

namespace sloth { namespace graphics {

	class Layer
	{
	protected:
		Renderer2D *m_Renderer;
		std::vector<Renderable2D*> m_Renderables;
		Shader *m_Shader;
		glm::mat4 m_Projection;
	protected:
		Layer(Renderer2D *renderer, Shader *shader, const glm::mat4 &projection);
	public:
		virtual ~Layer();
		virtual void add(Renderable2D *renderable);
		virtual void render();
	};
} }

#endif // !SLOTH_LAYER_H_
