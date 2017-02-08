/************************************************************************
* @project 		:  sloth
* @class   		:  Maths
* @version 		:  v1.0.0
* @description	:  ���ڲ��� OpenGL gui shader ����
* @author		:  Oscar Shen
* @creat 		:  2016��12��3��14:09:57
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

		// ��õѿ�����ά���� pos λ�õ���ά�����ֵ������
		// ����֪���������������꣬����ƽ���ϵ���һ������
		static float barycentric(glm::vec3 &v1, glm::vec3 &v2, glm::vec3 &v3, glm::vec2 &pos);

		/************************************************************************
		 * @description	: ���� 2D ת�����󣬰���ƽ�ơ����ŷ�������������ת������
						  ����˳���������ţ���ƽ��
		 * @author		: Oscar Shen
		 * @creat		: 2017��2��8��16:52:25
		 ***********************************************************************/
		static glm::mat4 createTransformationMatrix(const glm::vec2 translation, const glm::vec2 scale);
	};


} }


#endif // !SLOTH_MATHS_H_
