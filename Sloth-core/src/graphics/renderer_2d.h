#pragma once
#ifndef SLOTH_RENDERER_2D
#define SLOTH_RENDERER_2D

#include "renderable_2d.h"

namespace sloth { namespace graphics {

	class Renderer2D 
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
		virtual void begin() {}
		virtual void sumbit(const Renderable2D *renderable) = 0;
		virtual void end() {}
		virtual void flush() = 0;
	};

} }

#endif // !SLOTH_RENDERER_2D