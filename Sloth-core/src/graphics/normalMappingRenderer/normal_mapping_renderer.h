/************************************************************************ 
 * @project 	:  sloth
 * @class   	:  NormalMappingRenderer
 * @version 	:  v1.0.0
 * @description :  ������ӳ��ʵ������Ⱦ������
 * @author		:  Oscar Shen
 * @creat 		:  2017��2��22��13:38:39
 * @revise 		:  
************************************************************************ 
 * Copyright @ OscarShen 2017. All rights reserved. 
************************************************************************/  
#pragma once
#ifndef SLOTH_NORMAL_MAPPING_RENDERER_H_
#define SLOTH_NORMAL_MAPPING_RENDERER_H_

#include <GL/glew.h>
#include <map>
#include <vector>
#include "../model/textured_model.hpp"
#include "../entities/entity.h"
#include "../../utils/maths.h"
#include "../normalMappingRenderer/normal_mapping_shader.h"

namespace sloth { namespace graphics {

		class NormalMappingRenderer
		{
		public:
			NormalMappingRenderer() {}
			NormalMappingRenderer(glm::mat4 &projection);

			/***********************************************************************
			* @description	: ��Ⱦ����ʵ��
			* @author		: Oscar Shen
			* @creat		: 2017��2��22��13:42:33
			***********************************************************************/
			void render(Entity &entity);

			/***********************************************************************
			* @description	: ��Ⱦ���ʵ��
			* @author		: Oscar Shen
			* @creat		: 2017��2��22��13:42:20
			***********************************************************************/
			void render(std::map<TexturedModel, std::vector<Entity>> &entities);

		private:
			/***********************************************************************
			* @description	: ׼��ģ�ͣ�һ��ģ�Ϳɶ�Ӧ���ʵ��
			* @author		: Oscar Shen
			* @creat		: 2017��2��22��13:39:41
			***********************************************************************/
			void prepareTexturedModel(const TexturedModel &model) const;

			/***********************************************************************
			* @description	: ׼��ʵ������ÿһ��ʵ����ƽ�ơ���ת�����ŵ���Ϣ���ص� OpenGL
			* @author		: Oscar Shen
			* @creat		: 2017��2��22��13:40:30
			***********************************************************************/
			void prepareInstance(Entity &entity);

			/***********************************************************************
			* @description	: ����Ⱦ���ûָ�Ĭ��
			* @author		: Oscar Shen
			* @creat		: 2017��2��22��13:41:02
			***********************************************************************/
			void unbindTexturedModel();
		};

	}
}
#endif // !SLOTH_NORMAL_MAPPING_RENDERER_H_
