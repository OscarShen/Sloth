#pragma once
#ifndef SLOTH_LIGHT_H_
#define SLOTH_LIGHT_H_

#include <glm/glm.hpp>
namespace sloth { namespace graphics {

	struct Light
	{
		glm::vec3 position;
		glm::vec3 color;

		Light(const glm::vec3 &position, const glm::vec3 &color)
			:position(position), color(color)
		{}
	};

} }


#endif // !SLOTH_LIGHT_H_
