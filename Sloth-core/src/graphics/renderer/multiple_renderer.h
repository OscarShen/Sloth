/************************************************************************
 * @project 	:  sloth
 * @class   	:  MultipleRenderer
 * @version 	:  v1.0.1
 * @description	:  MultipleRenderer ��װ�� StaticRenderer �� TerrainRenderer
 				   ����ͨ����ͬ�Ĳ�����ģ�ͻ��ߵ��ν�����Ⱦ
 * @author		:  Oscar Shen
 * @creat 		:  2016��10��3��14:09:57
 * @revise 		:  2017��2��9��14:07:00
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
		* @description	: ����һ���ƹ������Ⱦ
		* @author		: Oscar Shen
		* @creat		: 2017��2��9��14:03:57
		***********************************************************************/
		void render(const Light &sun, const RawCamera &camera);

		/************************************************************************
		* @description	: ����ƹ�����������Ⱦ���ƹ������Ϊ GLSL_MAX_LIGHTS ��
		* @author		: Oscar Shen
		* @creat		: 2017��2��9��14:03:27
		***********************************************************************/
		void render(const std::vector<Light> &lights, const RawCamera &camera);
		void submitTerrain(const Terrain &terrain);
		void submitEntity(const Entity &entity);
	};

} }

#endif // !SLOTH_MULTIPLE_RENDERER_H_
