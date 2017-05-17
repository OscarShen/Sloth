/************************************************************************
 * @project 		:  sloth
 * @class   		:  Light
 * @version 		:  v1.0.0
 * @description	:  ʹ��һ�� struct ���洢�ƹ���Ϣ����λ�á���ɫ��˥��
 * @author		:  Oscar Shen
 * @creat 		:  2016��12��8��14:52:32
 * @revise 		:  2017��2��9��14:53:47
 ************************************************************************
 * Copyright @ OscarShen 2017. All rights reserved.
*************************************************************************/

#pragma once
#ifndef SLOTH_LIGHT_H_
#define SLOTH_LIGHT_H_
#include <sloth.h>
namespace sloth {

	struct Light
	{
		glm::vec3 position;
		glm::vec3 color;
		glm::vec3 attenuation = glm::vec3(1.0f, 0.0f, 0.0f);

		constexpr Light(const glm::vec3 &position, const glm::vec3 &color)
			:position(position), color(color) {}
		constexpr Light(const glm::vec3 &position, const glm::vec3 &color, const glm::vec3 &attenuation)
			: position(position), color(color), attenuation(attenuation) {}
	};

}


#endif // !SLOTH_LIGHT_H_
