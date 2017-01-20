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
		void render(const Light &sun, const Camera &camera);
		void submitTerrain(const Terrain &terrain);
		void submitEntity(const Entity &entity);
	};

} }

#endif // !SLOTH_MULTIPLE_RENDERER_H_
