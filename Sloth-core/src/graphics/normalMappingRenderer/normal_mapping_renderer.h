/************************************************************************ 
 * @project 	:  sloth
 * @class   	:  NormalMappingRenderer
 * @version 	:  v1.0.0
 * @description :  带法线映射实例的渲染操作类
 * @author		:  Oscar Shen
 * @creat 		:  2017年2月22日13:38:39
 * @revise 		:  
************************************************************************ 
 * Copyright @ OscarShen 2017. All rights reserved. 
************************************************************************/  
#pragma once
#ifndef SLOTH_NORMAL_MAPPING_RENDERER_H_
#define SLOTH_NORMAL_MAPPING_RENDERER_H_

#include <GL/glew.h>
#include <unordered_map>
#include <list>
#include <memory>
#include "../model/textured_model.hpp"
#include "../entities/entity.h"
#include "../../utils/maths.h"
#include "../normalMappingRenderer/normal_mapping_shader.h"

namespace sloth { namespace graphics {

		class NormalMappingRenderer
		{
		public:
			typedef std::unordered_map<TexturedModel, std::list<std::shared_ptr<Entity>>> MapedEntities;
			typedef std::shared_ptr<Entity> Entity_s;
			NormalMappingRenderer() {}
			NormalMappingRenderer(glm::mat4 &projection);

			/***********************************************************************
			* @description	: 渲染单个实例
			* @author		: Oscar Shen
			* @creat		: 2017年2月22日13:42:33
			***********************************************************************/
			void render(Entity_s &entity);

			/***********************************************************************
			* @description	: 渲染多个实例
			* @author		: Oscar Shen
			* @creat		: 2017年2月22日13:42:20
			***********************************************************************/
			void render(MapedEntities &entities);

		private:
			/***********************************************************************
			* @description	: 准备模型，一个模型可对应多个实例
			* @author		: Oscar Shen
			* @creat		: 2017年2月22日13:39:41
			***********************************************************************/
			void prepareTexturedModel(const TexturedModel &model) const;

			/***********************************************************************
			* @description	: 准备实例，将每一个实例的平移、旋转、缩放等信息加载到 OpenGL
			* @author		: Oscar Shen
			* @creat		: 2017年2月22日13:40:30
			***********************************************************************/
			void prepareInstance(Entity_s &entity);

			/***********************************************************************
			* @description	: 将渲染设置恢复默认
			* @author		: Oscar Shen
			* @creat		: 2017年2月22日13:41:02
			***********************************************************************/
			void unbindTexturedModel();
		};

	}
}
#endif // !SLOTH_NORMAL_MAPPING_RENDERER_H_

