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

		// 求得笛卡尔二维坐标 pos 位置的三维坐标插值的坐标
		// 即已知三角形中两个坐标，求在平面上的另一个坐标
		static float barycentric(glm::vec3 &v1, glm::vec3 &v2, glm::vec3 &v3, glm::vec2 &pos);
	};


} }


#endif // !SLOTH_MATHS_H_
