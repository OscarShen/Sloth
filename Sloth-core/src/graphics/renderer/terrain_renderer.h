/************************************************************************
* @project 		:  sloth
* @class   		:  TerrainRenderer
* @version 		:  v1.0.0
* @description	:  terrain ����Ⱦ������
* @author		:  Oscar Shen
* @creat 		:  2016��12��13��21:56:23
* @revise 		:
************************************************************************
* Copyright @ OscarShen 2016. All rights reserved.
************************************************************************/
#pragma once
#ifndef SLOTH_TERRAIN_RENDERER_H_
#define SLOTH_TERRAIN_RENDERER_H_
#include "../shader/terrain_shader.h"
#include "../terrain/terrain.h"
#include "../model/textured_model.hpp"
#include "../entities/entity.h"
#include "../../utils/maths.h"
#include <glm/glm.hpp>
#include <vector>

namespace sloth { namespace graphics {

	class TerrainRenderer
	{
	public:
		TerrainRenderer() {}
		TerrainRenderer(glm::mat4 &projection);
		~TerrainRenderer() {}

		void render(std::vector<Terrain*> &terrain);

	private:
		void prepareTerrain(Terrain &terrain);

		void loadModelMatrix(Terrain &terrain);

		void bindMultiTerrain(Terrain &terrain);
	};



} }


#endif // !SLOTH_TERRAIN_RENDERER_H_
