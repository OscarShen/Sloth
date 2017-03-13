#include "textured_model.hpp"

bool sloth::graphics::operator<(const TexturedModel & left, const TexturedModel & right)
{
	return left.getRawModel().getVaoID() < right.getRawModel().getVaoID();
}

bool sloth::graphics::operator==(const TexturedModel & left, const TexturedModel & right)
{
	return left.getRawModel().getVertexCount() == right.getRawModel().getVertexCount() &&
		left.getRawModel().getVaoID() == right.getRawModel().getVaoID() &&
		left.getTexture().getID() == right.getTexture().getID();
}
