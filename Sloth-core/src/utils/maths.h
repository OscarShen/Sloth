#pragma once
#ifndef SLOTH_MATHS_H_
#define SLOTH_MATHS_H_
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace sloth { namespace util {

	class Maths
	{
	public:
		static glm::mat4 createModelMatrix(const glm::vec3 &position, float rotX, float rotY, float rotZ, float scale);
	};


} }


#endif // !SLOTH_MATHS_H_
