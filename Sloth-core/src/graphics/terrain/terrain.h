#pragma once
#ifndef SLOTH_TERRAIN_H_
#define SLOTH_TERRAIN_H_
#include "../model/raw_model.hpp"
#include "../engine/loader.h"
#include "../setup/macro.h"
#include "multi_terrain.h"
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
		MultiTerrain m_Multi;
		std::vector<std::vector<float>> heights;

	public:
		Terrain(int gridX, int gridZ, unsigned int texID, Loader & loader, std::string heightMapPath);
		Terrain(int gridX, int gridZ, MultiTerrain m_Multi, Loader & loader, std::string heightMapPath);
		inline RawModel getModel() const { return m_Model; }
		inline const MultiTerrain& getMultiTerrain() const { return m_Multi; }
		inline float getX() const { return m_X; }
		inline float getZ() const { return m_Z; }
		// ��ȡ���εĸ߶�ֵ������߶�ֵ���������Բ�ֵ
		float getHeightOfTerrain(float worldX, float worldZ);

	private:
		RawModel generateTerrain(Loader &loader, std::string heightMapPath);
		float getHeight(int x, int z, util::BufferedImage *heightMap);
		glm::vec3 calculateNormal(int x, int z, util::BufferedImage *heightMap);
	};

} }



#endif // !SLOTH_TERRAIN_H_
