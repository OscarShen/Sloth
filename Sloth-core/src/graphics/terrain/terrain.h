#pragma once
#ifndef SLOTH_TERRAIN_H_
#define SLOTH_TERRAIN_H_
#include "../model/raw_model.hpp"
#include "../engine/loader.h"
#include "../setup/macro.h"
#include "multi_terrain.h"

#include <vector>

namespace sloth { namespace graphics {

	class Terrain
	{
	private:
		float m_X;
		float m_Z;
		RawModel m_Model;
		MultiTerrain m_Multi;

	public:
		Terrain(int gridX, int gridZ, unsigned int texID, Loader & loader);
		Terrain(int gridX, int gridZ, MultiTerrain m_Multi, Loader & loader);
		inline RawModel getModel() const { return m_Model; }
		inline const MultiTerrain& getMultiTerrain() const { return m_Multi; }
		inline float getX() const { return m_X; }
		inline float getZ() const { return m_Z; }

	private:
		RawModel generateTerrain(Loader &loader);
	};

} }



#endif // !SLOTH_TERRAIN_H_
