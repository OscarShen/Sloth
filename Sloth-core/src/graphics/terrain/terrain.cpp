#include "terrain.h"

namespace sloth { namespace graphics {
	Terrain::Terrain(int gridX, int gridZ, unsigned int texID, Loader & loader)
		:m_X(gridX), m_Z(gridZ), m_TexID(texID)
	{
		m_Model = generateTerrain(loader);
	}

	RawModel Terrain::generateTerrain(Loader & loader)
	{
		int count = TERRAIN_VERTEX_COUNT * TERRAIN_VERTEX_COUNT;
		std::vector<glm::vec3> vertices(count, glm::vec3(0.0f));
		std::vector<glm::vec3> normals(count, glm::vec3(0.0f));
		std::vector<glm::vec2> texCoords(count, glm::vec2(0.0f));
		std::vector<unsigned int> indices(
			6 * (TERRAIN_VERTEX_COUNT - 1) * (TERRAIN_VERTEX_COUNT - 1), 0);
		int vertexPointer = 0;
		for (int i = 0; i < TERRAIN_VERTEX_COUNT; ++i) {
			for (int j = 0; j < TERRAIN_VERTEX_COUNT; ++j) {
				vertices[vertexPointer].x = static_cast<float>(j) / (TERRAIN_VERTEX_COUNT - 1) * TERRAIN_SIZE;
				//vertices[vertexPointer].y = 0.0f;
				vertices[vertexPointer].z = static_cast<float>(i) / (TERRAIN_VERTEX_COUNT - 1) * TERRAIN_SIZE;
				//normals[vertexPointer].x = 0.0f;
				normals[vertexPointer].y = 1.0f;
				//normals[vertexPointer].z = 0.0f;
				texCoords[vertexPointer].x = static_cast<float>(j) / (TERRAIN_VERTEX_COUNT - 1);
				texCoords[vertexPointer].y = static_cast<float>(i) / (TERRAIN_VERTEX_COUNT - 1);
				++vertexPointer;
			}
		}
		int pointer = 0;
		for (int gz = 0; gz < TERRAIN_VERTEX_COUNT - 1; ++gz) {
			for (int gx = 0; gx < TERRAIN_VERTEX_COUNT - 1; ++gx) {
				int topLeft = gz * TERRAIN_VERTEX_COUNT + gx;
				int topRight = topLeft + 1;
				int bottomLeft = (gz + 1) *TERRAIN_VERTEX_COUNT + gx;
				int bottomRight = bottomLeft + 1;
				indices[pointer++] = topLeft;
				indices[pointer++] = bottomLeft;
				indices[pointer++] = topRight;
				indices[pointer++] = topRight;
				indices[pointer++] = bottomLeft;
				indices[pointer++] = bottomRight;
			}
		}
		return loader.loadToVAO(vertices, texCoords, normals, indices);
	}
} }
