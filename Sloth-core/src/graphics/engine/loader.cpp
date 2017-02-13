#include "loader.h"

namespace sloth { namespace graphics {

	Loader::~Loader()
	{
		cleanUp();
	}

	RawModel Loader::loadToVAO(std::vector<glm::vec3>& positions,
		std::vector<glm::vec2>& texCoords, std::vector<glm::vec3>& normals,
		std::vector<unsigned int>& indices)
	{
		VertexArray *va = createVAO();
		va->addBuffer(new Buffer(&positions[0].x, positions.size() * 3, 3), 0);
		va->addBuffer(new Buffer(&texCoords[0].x, texCoords.size() * 2, 2), 1);
		va->addBuffer(new Buffer(&normals[0].x, normals.size() * 3, 3), 2);
		va->addElementBuffer(new IndexBuffer(&indices[0], indices.size()));
		return RawModel(va->getVaoID(), indices.size());
	}

	RawModel Loader::loadToVAO(std::vector<glm::vec2>& positions, std::vector<glm::vec2>& texCoords)
	{
		VertexArray *va = createVAO();
		va->addBuffer(new Buffer(&positions[0].x, positions.size() * 2, 2), 0);
		va->addBuffer(new Buffer(&texCoords[0].x, texCoords.size() * 2, 2), 1);
		return RawModel(va->getVaoID(), positions.size());
	}

	RawModel Loader::loadToVAO(std::vector<glm::vec3>& positions)
	{
		VertexArray *va = createVAO();
		va->addBuffer(new Buffer(&positions[0].x, positions.size() * 3, 3), 0);
		return RawModel(va->getVaoID(), positions.size());
	}

	RawModel Loader::loadToVAO(std::vector<float>& positions, int dimention)
	{
		VertexArray *va = createVAO();
		va->addBuffer(new Buffer(positions.data(), positions.size(), dimention), 0);
		return RawModel(va->getVaoID(), positions.size() / dimention);
	}

	void Loader::cleanUp()
	{
		for (size_t i = 0; i < m_Vaos.size(); ++i) {
			delete m_Vaos[i];
		}
		m_Vaos.clear();
	}

	VertexArray* Loader::createVAO()
	{
		auto va = new VertexArray();
		m_Vaos.push_back(va);
		return va;
	}
} }

