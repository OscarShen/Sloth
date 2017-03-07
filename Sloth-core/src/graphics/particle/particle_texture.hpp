/************************************************************************ 
 * @project 	:  sloth
 * @class   	:  ParticleTexture
 * @version 	:  v1.0.0
 * @description :  粒子纹理的数据类
 * @author		:  Oscar Shen
 * @creat 		:  2017年3月6日13:44:25
 * @revise 		:  
************************************************************************ 
 * Copyright @ OscarShen 2017. All rights reserved. 
************************************************************************/  
#pragma once
#ifndef SLOTH_PARTICLE_tEXTURE
#define SLOTH_PARTICLE_tEXTURE

#include <unordered_map>

namespace sloth { namespace graphics {

	class ParticleTexture
	{
	private:
		unsigned int m_TextureID;
		unsigned int m_NumberOfRows;
		bool m_Additive;

	public:
		constexpr ParticleTexture(unsigned int textureID, unsigned int numberOfRows, bool additive = false)
			:m_TextureID(textureID), m_NumberOfRows(numberOfRows), m_Additive(additive) {}

		inline unsigned int getTextureID() const { return m_TextureID; }
		inline unsigned int getNumberOfRows() const { return m_NumberOfRows;  }
		inline bool isAdditive() const { return m_Additive; }

		friend bool operator==(const ParticleTexture& left, const ParticleTexture& right);
	};

} }

namespace std {
	template <>
	struct hash<sloth::graphics::ParticleTexture> {
		std::size_t operator()(const sloth::graphics::ParticleTexture& texture) const {
			return texture.getTextureID() * 31 + texture.getNumberOfRows() * 131;
		}
	};
}


#endif // !SLOTH_PARTICLE_tEXTURE
