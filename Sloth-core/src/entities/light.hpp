/************************************************************************
 * @project 		:  sloth
 * @class   		:  Light
 * @version 		:  v1.0.0
 * @description	:  使用一个 struct 来存储灯光信息——位置、颜色、衰减
 * @author		:  Oscar Shen
 * @creat 		:  2016年12月8日14:52:32
 * @revise 		:  2017年2月9日14:53:47
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
