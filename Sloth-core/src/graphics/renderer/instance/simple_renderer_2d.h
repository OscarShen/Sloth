#pragma once
#ifndef SLOTH_SIMPLE_RENDERER_2D_H_
#define SLOTH_SIMPLE_RENDERER_2D_H_

#include "../renderer_2d.h"
#include <deque>
namespace sloth { namespace graphics {

	class Renderer2D;
	class SimpleRenderer2D :public Renderer2D
	{
	protected:
		std::deque<const Renderable2D*> m_RenderQueue;

	public:
		virtual void flush() override;
		virtual void submit(const Renderable2D *renderable) override;
	};

} }



#endif // !SLOTH_SIMPLE_RENDERER_2D_H_
