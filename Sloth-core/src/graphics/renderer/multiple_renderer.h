/************************************************************************
 * @project 	:  sloth
 * @class   	:  MultipleRenderer
 * @version 	:  v1.0.1
 * @description	:  MultipleRenderer 封装自 StaticRenderer 和 TerrainRenderer
 				   可以通过相同的操作对模型或者地形进行渲染
 * @author		:  Oscar Shen
 * @creat 		:  2016年10月3日14:09:57
 * @revise 		:  2017年2月9日14:07:00
 ************************************************************************
 * Copyright @ OscarShen 2017. All rights reserved.
 ************************************************************************/
#pragma once
#ifndef SLOTH_MULTIPLE_RENDERER_H_
#define SLOTH_MULTIPLE_RENDERER_H_

#include "../renderer/static_renderer.h"
#include "../renderer/terrain_renderer.h"
#include "../model/textured_model.hpp"
#include "../setup/global_function.h"
#include <map>
#include <vector>

namespace sloth { namespace graphics {

	class MultipleRenderer
	{
	private:
		StaticRenderer *m_StaticRenderer;

		TerrainRenderer *m_TerrainRenderer;

		std::map<TexturedModel, std::vector<Entity>> m_Entities;
		std::vector<Terrain> m_Terrains;

	public:
		MultipleRenderer();
		~MultipleRenderer();
		/************************************************************************
		* @description	: 传入一个灯光进行渲染
		* @author		: Oscar Shen
		* @creat		: 2017年2月9日14:03:57
		***********************************************************************/
		void render(const Light &sun, const RawCamera &camera);

		/************************************************************************
		* @description	: 传入灯光和相机进行渲染，灯光最大数为 GLSL_MAX_LIGHTS 宏
		* @author		: Oscar Shen
		* @creat		: 2017年2月9日14:03:27
		***********************************************************************/
		void render(const std::vector<Light> &lights, const RawCamera &camera);
		void submitTerrain(const Terrain &terrain);
		void submitEntity(const Entity &entity);
	};

} }

#endif // !SLOTH_MULTIPLE_RENDERER_H_
