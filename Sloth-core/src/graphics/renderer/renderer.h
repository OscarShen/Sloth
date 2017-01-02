#pragma once
#ifndef SLOTH_RENDERER
#define SLOTH_RENDERER

namespace sloth { namespace graphics {

	class Renderer
	{
	public:
		virtual void begin() {}
		virtual void end() {}
		virtual void flush() = 0;
		virtual ~Renderer() {}
	};

} }
#endif // !SLOTH_RENDERER_2D