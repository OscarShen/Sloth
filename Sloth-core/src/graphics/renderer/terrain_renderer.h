#pragma once
#ifndef SLOTH_TERRAIN_RENDERER_H_
#define SLOTH_TERRAIN_RENDERER_H_
#include "../shader/terrain_shader.h"
#include "../terrain/terrain.h"
#include "../model/textured_model.hpp"
#include "../texture/texture_manager_2d.h"
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

		void render(std::vector<Terrain> &terrain);

	private:
		void prepareTerrain(const Terrain &terrain);

		void loadModelMatrix(Terrain &terrain);
	};



} }


#endif // !SLOTH_TERRAIN_RENDERER_H_
