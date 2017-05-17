#include "terrain.h"

namespace sloth { 
	Terrain::Terrain(int gridX, int gridZ, unsigned int ID, Loader & loader, std::string heightMapPath)
		:m_X(gridX * TERRAIN_SIZE), m_Z(gridZ * TERRAIN_SIZE), m_Pack(TerrainTexturePack(ID, 0, 0, 0, 0))
	{
		m_Model = generateTerrain(loader, heightMapPath);
	}

	Terrain::Terrain(int gridX, int gridZ, TerrainTexturePack m_Pack, Loader & loader, std::string heightMapPath)
		: m_X(gridX * TERRAIN_SIZE), m_Z(gridZ * TERRAIN_SIZE), m_Pack(m_Pack)
	{
		m_Model = generateTerrain(loader, heightMapPath);
	}

	float Terrain::getHeightOfTerrain(float worldX, float worldZ) const
	{
		float terrainX = worldX - m_X;
		float terrainZ = worldZ - m_Z;
		// 地形的方格个数为边上顶点的个数减一
		float gridSquareSize = TERRAIN_SIZE / static_cast<float>(heights.size() - 1);
		float oneDivideGridSquareSize = 1.0f / gridSquareSize;
		// 给方格编号，左上角为0,0
		unsigned int gridX = (unsigned int) glm::floor(terrainX * oneDivideGridSquareSize);
		unsigned int gridZ = (unsigned int) glm::floor(terrainZ * oneDivideGridSquareSize);
		if (gridX >= heights.size() - 1 || gridZ >= heights.size() - 1 || gridX < 0 || gridZ < 0) {
			return 0;
		}
		// 取得坐标点再单个网格中的坐标，左上角为 (0,0) 右下角为（1,1）
		float xCoord = std::fmodf(terrainX, gridSquareSize) * oneDivideGridSquareSize;
		float zCoord = std::fmodf(terrainZ, gridSquareSize) * oneDivideGridSquareSize;
		
		// 一个网格由两个三角形组成，通过 xCoord 和 1-zCoord 来判断点落在哪个三角形内
		// 本方法默认三角形的公共边为反对角线
		// 然后在进行线性插值
		float interpolation = 0.0f;
		if (xCoord <= (1 - zCoord)) {
			interpolation = Maths::barycentric(
				glm::vec3(0.0f, heights[gridX][gridZ], 0.0f),
				glm::vec3(1.0f, heights[gridX + 1][gridZ], 0.0f),
				glm::vec3(0.0f, heights[gridX][gridZ + 1], 1.0f),
				glm::vec2(xCoord, zCoord)
			);
		}
		else {
			interpolation = Maths::barycentric(
				glm::vec3(1.0f, heights[gridX + 1][gridZ], 0.0f),
				glm::vec3(1.0f, heights[gridX + 1][gridZ + 1], 1.0f),
				glm::vec3(0.0f, heights[gridX][gridZ + 1], 1.0f),
				glm::vec2(xCoord, zCoord)
			);
		}
		return interpolation;
	}

	RawModel Terrain::generateTerrain(Loader & loader, std::string heightMapPath)
	{
		BufferedImage *image = new BufferedImage(heightMapPath);
		int vertex_count = image->getHeight();
		
		// 记录各个顶点的高度 height
		heights = std::vector<std::vector<float>>(vertex_count, std::vector<float>(vertex_count, 0));

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
				float height = getHeight(j, i, image);
				// 记录每一点的 height
				heights[j][i] = height;

				vertices[vertexPointer].x = j * raw_vertex_width;
				vertices[vertexPointer].y = height;
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

	float Terrain::getHeight(int x, int z, BufferedImage *heightMap)
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
	glm::vec3 Terrain::calculateNormal(int x, int z, BufferedImage * heightMap)
	{
		float heightL = getHeight(x - 1, z, heightMap);
		float heightR = getHeight(x + 1, z, heightMap);
		float heightD = getHeight(x, z - 1, heightMap);
		float heightU = getHeight(x, z + 1, heightMap);
		glm::vec3 normal(heightL - heightR, 2.0f, heightD - heightU);
		return glm::normalize(normal);
	}
} 
