#pragma once
#ifndef SLOTH_TERRAIN_MULTI_H_
#define SLOTH_TERRAIN_MULTI_H_

namespace sloth { namespace graphics {

	// Contains several terrain multitexture.
	// Default pack contains four channel, witch
	// are background(black), red, green, blue.
	class MultiTerrain
	{
	private:
		// TexID of background texture
		unsigned int m_Background;
		// TexID of red texture
		unsigned int m_Red;
		// TexID of green texture
		unsigned int m_Green;
		// TexID of blue texture
		unsigned int m_Blue;
		// TexID of terrain design
		unsigned int m_BlendMap;

	public:
		constexpr MultiTerrain(unsigned int background_texID,
			unsigned int red_texID,
			unsigned int green_texID,
			unsigned int blue_texID,
			unsigned int blendMap_texID)
			:m_Background(background_texID), m_Red(red_texID), m_Green(green_texID), 
			m_Blue(blue_texID), m_BlendMap(blendMap_texID) {}
		~MultiTerrain() {}

		inline unsigned int getBackgroundTexID() { return m_Background; }
		inline unsigned int getRedTexID() { return m_Red; }
		inline unsigned int getGreenTexID() { return m_Green; }
		inline unsigned int getBlueTexID() { return m_Blue; }
		inline unsigned int getBlendMapTexID() { return m_BlendMap; }
	};

} }




#endif // !SLOTH_TERRAIN_MULTI_H_
