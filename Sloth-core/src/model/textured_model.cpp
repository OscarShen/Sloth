#include "textured_model.hpp"

bool sloth::operator<(const TexturedModel & left, const TexturedModel & right)
{
	return left.getRawModel().getVaoID() < right.getRawModel().getVaoID();
}

bool sloth::operator==(const TexturedModel & left, const TexturedModel & right)
{
	return left.getRawModel().getVertexCount() == right.getRawModel().getVertexCount() &&
		left.getRawModel().getVaoID() == right.getRawModel().getVaoID() &&
		left.getTexture().getID() == right.getTexture().getID();
}
