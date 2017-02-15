#include "textured_model.hpp"

bool sloth::graphics::operator<(const TexturedModel & left, const TexturedModel & right)
{
	return left.getRawModel().getVaoID() < right.getRawModel().getVaoID();
}
