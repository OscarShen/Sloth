#pragma once
#ifndef SLOTH_TERRAIN_H_
#define SLOTH_TERRAIN_H_
#include "../model/raw_model.hpp"
#include "../engine/loader.h"
#include "../setup/macro.h"

#include <vector>

namespace sloth { namespace graphics {

	class Terrain
	{
	private:
		float m_X;
		float m_Z;
		RawModel m_Model;
		unsigned int m_TexID;

	public:
		Terrain(int gridX, int gridZ, unsigned int texID, Loader & loader);
		inline RawModel getModel() const { return m_Model; }
		inline unsigned int getTexID() const { return m_TexID; }
		inline float getX() const { return m_X; }
		inline float getZ() const {return m_Z;}

	private:
		RawModel generateTerrain(Loader &loader);
	};

} }



#endif // !SLOTH_TERRAIN_H_
