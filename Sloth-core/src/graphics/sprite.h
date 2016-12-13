#pragma once
#ifndef SLOTH_SPRITE_H_
#define SLOTH_SPRITE_H_

#include "renderable_2d.h"

namespace sloth { namespace graphics {

	class Sprite : public Renderable2D
	{
	public:
		Sprite(float x, float y, float width, float height, glm::vec4 &color);
	};
} }

#endif // !SLOTH_SPRITE_H_
