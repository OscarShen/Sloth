/************************************************************************
* @project 		:  sloth
* @class   		:  TerrainRenderer
* @version 		:  v1.0.0
* @description	:  terrain 的渲染操作类
* @author		:  Oscar Shen
* @creat 		:  2016年12月13日21:56:23
* @revise 		:
************************************************************************
* Copyright @ OscarShen 2016. All rights reserved.
************************************************************************/
#pragma once
#ifndef SLOTH_TERRAIN_RENDERER_H_
#define SLOTH_TERRAIN_RENDERER_H_
#include <sloth.h>
#include "../shader/terrain_shader.h"
#include "../terrain/terrain.h"
#include "../model/textured_model.hpp"
#include "../entities/entity.h"
#include "../utils/maths.h"

namespace sloth { 

	class TerrainRenderer
	{
		typedef std::shared_ptr<Terrain> Terrain_s;
	public:
		TerrainRenderer() {}
		TerrainRenderer(glm::mat4 &projection);
		~TerrainRenderer() {}

		void render(std::list<Terrain_s> &terrain, unsigned int shadowMap);

	private:
		void prepareTerrain(Terrain &terrain);

		void loadModelMatrix(Terrain &terrain);

		void bindMultiTerrain(Terrain &terrain);
	};



} 


#endif // !SLOTH_TERRAIN_RENDERER_H_
