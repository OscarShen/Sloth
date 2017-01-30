#include "terrain.h"

namespace sloth { namespace graphics {
	Terrain::Terrain(int gridX, int gridZ, unsigned int texID, Loader & loader, std::string heightMapPath)
		:m_X(gridX * TERRAIN_SIZE), m_Z(gridZ * TERRAIN_SIZE), m_Multi(MultiTerrain(texID, 0, 0, 0, 0))
	{
		m_Model = generateTerrain(loader, heightMapPath);
	}

	Terrain::Terrain(int gridX, int gridZ, MultiTerrain m_Multi, Loader & loader, std::string heightMapPath)
		: m_X(gridX * TERRAIN_SIZE), m_Z(gridZ * TERRAIN_SIZE), m_Multi(m_Multi)
	{
		m_Model = generateTerrain(loader, heightMapPath);
	}

	RawModel Terrain::generateTerrain(Loader & loader, std::string heightMapPath)
	{
		util::BufferedImage *image = new util::BufferedImage(heightMapPath);
		int vertex_count = image->getHeight();

		int count = vertex_count * vertex_count;
		std::vector<glm::vec3> vertices(count, glm::vec3(0.0f));
		std::vector<glm::vec3> normals(count, glm::vec3(0.0f));
		std::vector<glm::vec2> texCoords(count, glm::vec2(0.0f));
		std::vector<unsigned int> indices(
			6 * (vertex_count - 1) * (vertex_count - 1), 0);
		int vertexPointer = 0;
		float raw_vertex_width = static_cast<float>(TERRAIN_SIZE) / (vertex_count - 1);
		float raw_texCoord_width = 1.0f / (vertex_count - 1);
		for (int i = 0; i < vertex_count; ++i) {
			for (int j = 0; j < vertex_count; ++j) {
				vertices[vertexPointer].x = j * raw_vertex_width;
				vertices[vertexPointer].y = getHeight(j, i, image);
				vertices[vertexPointer].z = i * raw_vertex_width;
				glm::vec3 normal = calculateNormal(j, i, image);
				normals[vertexPointer].x = normal.x;
				normals[vertexPointer].y = normal.y;
				normals[vertexPointer].z = normal.z;
				texCoords[vertexPointer].x = j * raw_texCoord_width;
				texCoords[vertexPointer].y = i * raw_texCoord_width;
				++vertexPointer;
			}
		}
		int pointer = 0;
		for (int gz = 0; gz < vertex_count - 1; ++gz) {
			for (int gx = 0; gx < vertex_count - 1; ++gx) {
				int topLeft = gz * vertex_count + gx;
				int topRight = topLeft + 1;
				int bottomLeft = (gz + 1) * vertex_count + gx;
				int bottomRight = bottomLeft + 1;
				indices[pointer++] = topLeft;
				indices[pointer++] = bottomLeft;
				indices[pointer++] = topRight;
				indices[pointer++] = topRight;
				indices[pointer++] = bottomLeft;
				indices[pointer++] = bottomRight;
			}
		}
		delete image;
		return loader.loadToVAO(vertices, texCoords, normals, indices);
	}

	float Terrain::getHeight(int x, int z, util::BufferedImage *heightMap)
	{
		if (x < 0 || x >= heightMap->getWidth() || z < 0 || z >= heightMap->getHeight()) {
			return 0.0f;
		}
		float height = static_cast<float>(heightMap->getRGB(x, z));
		height += TERRAIN_MAX_PIXEL_COLOR / 2.0f;
		height /= TERRAIN_MAX_PIXEL_COLOR / 2.0f;
		height *= TERRAIN_MAX_HEIGHT;
		return height;
	}
	glm::vec3 Terrain::calculateNormal(int x, int z, util::BufferedImage * heightMap)
	{
		float heightL = getHeight(x - 1, z, heightMap);
		float heightR = getHeight(x + 1, z, heightMap);
		float heightD = getHeight(x, z - 1, heightMap);
		float heightU = getHeight(x, z + 1, heightMap);
		glm::vec3 normal(heightL - heightR, 2.0f, heightD - heightU);
		return glm::normalize(normal);
	}
} }
