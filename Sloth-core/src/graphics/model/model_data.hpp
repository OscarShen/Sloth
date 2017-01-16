#pragma once
#ifndef SLOTH_MODEL_DATA_H_
#define SLOTH_MODEL_DATA_H_

#include <vector>
#include <glm/glm.hpp>
namespace sloth { namespace graphics {

	struct ModelData
	{
		std::vector<glm::vec3> positions;
		std::vector<glm::vec2> texCoords;
		std::vector<glm::vec3> normals;
		std::vector<unsigned int> indices;

		ModelData() {}

		ModelData(
			const std::vector<glm::vec3> &positions,
			const std::vector<glm::vec2> &texCoords,
			const std::vector<glm::vec3> &normals,
			const std::vector<unsigned int> &indices
		) :positions(positions), texCoords(texCoords), normals(normals), indices(indices) {}
	};

} }


#endif // !SLOTH_MODEL_DATA_H_
