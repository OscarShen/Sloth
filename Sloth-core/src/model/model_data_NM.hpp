/************************************************************************ 
 * @project 	:  sloth
 * @class   	:  ModelDataNM
 * @version 	:  v1.0.0
 * @description :  记录包含法线贴图的模型数据结构
 * @author		:  Oscar Shen
 * @creat 		:  2017年2月21日21:34:41
 * @revise 		:  
************************************************************************ 
 * Copyright @ OscarShen 2017. All rights reserved. 
************************************************************************/  
#pragma once
#ifndef SLOTH_MODEL_DATA_NM_H_
#define SLOTH_MODEL_DATA_NM_H_

#include <sloth.h>
namespace sloth {

	struct ModelDataNM
	{
		std::vector<glm::vec3> positions;
		std::vector<glm::vec2> texCoords;
		std::vector<glm::vec3> normals;
		std::vector<glm::vec3> tangents;
		std::vector<unsigned int> indices;
	};

} 


#endif // !SLOTH_MODEL_DATA_NM_H_
