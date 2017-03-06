#include "particle_texture.hpp"

bool sloth::graphics::operator==(const ParticleTexture & left, const ParticleTexture & right)
{
	return left.m_TextureID == right.m_TextureID && left.m_NumberOfRows == right.m_NumberOfRows;
}
