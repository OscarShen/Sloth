#include "loader.h"

namespace sloth { namespace graphics {

	Loader::~Loader()
	{
		for (size_t i = 0; i < m_Vaos.size(); ++i) {
			delete m_Vaos[i];
		}
	}

	RawModel Loader::loadToVAO(ModelData * modeldata)
	{
		return loadToVAO(modeldata->positions, modeldata->texCoords, modeldata->normals, modeldata->indices);
	}

	RawModel Loader::loadToVAO(std::vector<glm::vec3>& positions, std::vector<glm::vec2>& texCoords, std::vector<glm::vec3>& normals, std::vector<unsigned int>& indices)
	{
		VertexArray *va = createVAO();
		va->addBuffer(new Buffer(&positions[0].x, positions.size() * 3, 3), 0);
		va->addBuffer(new Buffer(&texCoords[0].x, texCoords.size() * 2, 2), 1);
		va->addBuffer(new Buffer(&normals[0].x, normals.size() * 3, 3), 2);
		va->addElementBuffer(new IndexBuffer(&indices[0], indices.size()));
		return RawModel(va->getVaoID(), indices.size());
	}

	VertexArray* Loader::createVAO()
	{
		m_Vaos.push_back(new VertexArray());
		return m_Vaos.back();
	}

} }

