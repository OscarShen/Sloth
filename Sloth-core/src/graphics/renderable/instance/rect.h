#pragma once
#ifndef SLOTH_RECTANGLE_H_
#define SLOTH_RECTANGLE_H_

#include "../renderable_2d.h"
#include "../../buffers/vertex_array.h"
#include "../../buffers/index_buffer.h"
#include "../../buffers/buffer.h"


namespace sloth { namespace graphics {

	class Rectangle:public Renderable2D
	{
	public:
		Rectangle(unsigned int shader);
		Rectangle(float x, float y,float width,float height, unsigned int shader);

		virtual ~Rectangle();

	private:
		void constr(float x, float y, float width, float height, unsigned int shader);
	};

} }


#endif // !SLOTH_RECTANGLE_H_
