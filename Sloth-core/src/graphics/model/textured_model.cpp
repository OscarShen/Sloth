#include "textured_model.hpp"

bool sloth::graphics::operator<(const TexturedModel & left, const TexturedModel & right)
{
	return left.m_TexID < right.m_TexID;
}
