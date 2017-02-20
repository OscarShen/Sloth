#pragma once
#ifndef SLOTH_TERRAIN_H_
#define SLOTH_TERRAIN_H_
#include "../model/raw_model.hpp"
#include "../engine/loader.h"
#include "terrain_texture_pack.hpp"
#include "../../utils/buffered_image.h"
#include "../../utils/maths.h"

#include <vector>

namespace sloth { namespace graphics {

	class Terrain
	{
	private:
		float m_X;
		float m_Z;
		RawModel m_Model;
		TerrainTexturePack m_Pack;
		std::vector<std::vector<float>> heights;

	public:
		Terrain(int gridX, int gridZ, unsigned int texID, Loader & loader, std::string heightMapPath);
		Terrain(int gridX, int gridZ, TerrainTexturePack m_Pack, Loader & loader, std::string heightMapPath);
		inline RawModel getModel() const { return m_Model; }
		inline const TerrainTexturePack& getTexturePack() const { return m_Pack; }
		inline float getX() const { return m_X; }
		inline float getZ() const { return m_Z; }
		// 获取地形的高度值，这个高度值经过了线性插值
		float getHeightOfTerrain(float worldX, float worldZ) const;

	private:
		RawModel generateTerrain(Loader &loader, std::string heightMapPath);
		float getHeight(int x, int z, util::BufferedImage *heightMap);
		glm::vec3 calculateNormal(int x, int z, util::BufferedImage *heightMap);
	};

} }



#endif // !SLOTH_TERRAIN_H_
