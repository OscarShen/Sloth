#pragma once
#ifndef SLOTH_RENDERER_2D
#define SLOTH_RENDERER_2D

#include "renderable_2d.h"

namespace sloth { namespace graphics {

	class Renderer2D 
	{
	public:
		virtual void begin() {}
		virtual void sumbit(const Renderable2D *renderable) = 0;
		virtual void end() {}
		virtual void flush() = 0;
	};

} }

#endif // !SLOTH_RENDERER_2D