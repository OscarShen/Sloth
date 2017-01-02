#pragma once
#ifndef SLOTH_RENDERER_2D
#define SLOTH_RENDERER_2D

#include "renderer.h"
#include "../renderable/renderable_2d.h"
#include <vector>
#include <glm/glm.hpp>

namespace sloth { namespace graphics {
	class Renderable2D;
	class Renderer2D : public Renderer
	{
	protected:
		std::vector<glm::mat4> m_TransformationStack;
		const glm::mat4 *m_TransformationBack;

	protected:
		Renderer2D()
		{
			m_TransformationStack.push_back(glm::mat4());
			m_TransformationBack = &m_TransformationStack.back();
		}

	public:
		void push(const glm::mat4 &matrix, bool override = false)
		{
			// TODO: Add to log!
			if(override)
				m_TransformationStack.push_back(matrix);
			else
				m_TransformationStack.push_back(m_TransformationStack.back() * matrix);

			m_TransformationBack = &m_TransformationStack.back();
		}

		void pop()
		{
			// TODO: Add to log!
			if (m_TransformationStack.size() > 1)
				m_TransformationStack.pop_back();

			m_TransformationBack = &m_TransformationStack.back();
		}

		inline const glm::mat4* backMatrix() { return m_TransformationBack; }

		virtual void submit(const Renderable2D *renderable) = 0;
	};
} }
#endif // !SLOTH_RENDERER_2D