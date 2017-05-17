/************************************************************************ 
 * @project 	:  sloth
 * @class   	:  ModelDataNM
 * @version 	:  v1.0.0
 * @description :  ��¼����������ͼ��ģ�����ݽṹ
 * @author		:  Oscar Shen
 * @creat 		:  2017��2��21��21:34:41
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
