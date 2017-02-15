#pragma once

#ifndef SLOTH_TERRAIN_TEXTURE_PACK
#define SLOTH_TERRAIN_TEXTURE_PACK

namespace sloth { namespace graphics {

	// Contains several terrain multitexture.
	// Default pack contains four channel, witch
	// are background(black), red, green, blue.
	class TerrainTexturePack
	{
	private:
		unsigned int m_Background;
		unsigned int m_Red;
		unsigned int m_Green;
		unsigned int m_Blue;
		unsigned int m_BlendMap;

	public:
		constexpr TerrainTexturePack(unsigned int background_ID,
			unsigned int red_ID,
			unsigned int green_ID,
			unsigned int blue_ID,
			unsigned int blendMap_ID)
			:m_Background(background_ID), m_Red(red_ID), m_Green(green_ID), 
			m_Blue(blue_ID), m_BlendMap(blendMap_ID) {}
		~TerrainTexturePack() {}

		inline unsigned int getBackgroundID() { return m_Background; }
		inline unsigned int getRedID() { return m_Red; }
		inline unsigned int getGreenID() { return m_Green; }
		inline unsigned int getBlueID() { return m_Blue; }
		inline unsigned int getBlendMapID() { return m_BlendMap; }
	};

} }
#endif // !SLOTH_TERRAIN_TEXTURE_PACK
