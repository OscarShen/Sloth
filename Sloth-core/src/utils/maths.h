/************************************************************************
* @project 		:  sloth
* @class   		:  Maths
* @version 		:  v1.0.0
* @description	:  用于操作 OpenGL gui shader 数据
* @author		:  Oscar Shen
* @creat 		:  2016年12月3日14:09:57
* @revise 		:
************************************************************************
* Copyright @ OscarShen 2016. All rights reserved.
************************************************************************/
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

		/************************************************************************
		 * @description	: 构造 2D 转换矩阵，包括平移、缩放分量，不包括旋转，矩阵
						  计算顺序是先缩放，再平移
		 * @author		: Oscar Shen
		 * @creat		: 2017年2月8日16:52:25
		 ***********************************************************************/
		static glm::mat4 createModelMatrix(const glm::vec2 translation, const glm::vec2 scale);

		static glm::vec3 rayPlaneIntersection(const glm::vec3 & ray_origin, const glm::vec3 & ray_dir,
			const glm::vec3 & p1, const glm::vec3 & p2, const glm::vec3 & p3);
	};


} }


#endif // !SLOTH_MATHS_H_
