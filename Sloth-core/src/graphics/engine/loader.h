#pragma once
#ifndef SLOTH_LOADER_H_
#define SLOTH_LOADER_H_

#include <GL/glew.h>
#include <vector>
#include <glm/glm.hpp>
#include <SOIL/SOIL.h>
#include "../buffers/index_buffer.h"
#include "../buffers/vertex_array.h"
#include "../model/raw_model.hpp"
#include "../model/model_data.hpp"

namespace sloth { namespace graphics {

	class Loader
	{
	private:
		std::vector<VertexArray*> m_Vaos;
		std::vector<unsigned int> m_Textures;

	public:
		Loader() {}
		~Loader();

		RawModel loadToVAO(ModelData *modeldata);

		RawModel loadToVAO(
			std::vector<glm::vec3> &positions,
			std::vector<glm::vec2> &texCoords,
			std::vector<glm::vec3> &normals,
			std::vector<unsigned int> &indices
		);

	private:
		VertexArray* createVAO();
	};


} }


#endif // !SLOTH_LOADER_H_
