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

	unsigned int Loader::loadToVAO(std::vector<float>& positions, std::vector<float>& texCoords)
	{
		VertexArray *va = createVAO();
		va->addBuffer(new Buffer(positions.data(), positions.size(), 2), 0);
		va->addBuffer(new Buffer(texCoords.data(), texCoords.size(), 2), 1);
		return va->getVaoID();
	}

	RawModel Loader::loadToVAO(std::vector<glm::vec3>& positions, std::vector<glm::vec2>& texCoords, std::vector<glm::vec3>& normals, std::vector<glm::vec3>& tangents, std::vector<unsigned int>& indices)
	{
		VertexArray *va = createVAO();
		va->addBuffer(new Buffer(&positions[0].x, positions.size() * 3, 3), 0);
		va->addBuffer(new Buffer(&texCoords[0].x, texCoords.size() * 2, 2), 1);
		va->addBuffer(new Buffer(&normals[0].x, normals.size() * 3, 3), 2);
		va->addBuffer(new Buffer(&tangents[0].x, tangents.size() * 3, 3), 3);
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

	unsigned int Loader::loadTexture(const std::string & fileName, bool alpha)
	{
		int width, height;
		unsigned char* image(nullptr);
		if (alpha)
			image = SOIL_load_image(fileName.c_str(), &width, &height, 0, SOIL_LOAD_RGBA);
		else
			image = SOIL_load_image(fileName.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
		auto id = setupTexture(width, height, image, alpha);
		// And finally free image data
		SOIL_free_image_data(image);
		m_Textures.push_back(id);
		return id;
	}

	unsigned int Loader::loadCubeMap(const std::vector<std::string>& cubeMapPaths, bool alpha)
	{
		unsigned int glID = 0;
		glCreateTextures(GL_TEXTURE_CUBE_MAP, 1, &glID);
		glBindTexture(GL_TEXTURE_CUBE_MAP, glID);
		int internalFormat = GL_RGB8;
		unsigned int ImageFormat = GL_RGB;
		auto SOIL_LOD_TYPE = SOIL_LOAD_RGB;
		if (alpha)
		{
			internalFormat = GL_RGBA8;
			ImageFormat = GL_RGBA;
			SOIL_LOD_TYPE = SOIL_LOAD_RGBA;
		}
		int width, height;
		for (size_t i = 0; i < cubeMapPaths.size(); ++i) {
			unsigned char* image = SOIL_load_image(cubeMapPaths[i].c_str(),
				&width, &height, 0, SOIL_LOD_TYPE);
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, internalFormat,
				width, height, 0, ImageFormat, GL_UNSIGNED_BYTE, image);
			SOIL_free_image_data(image);
		}
		glTextureParameteri(glID, GL_TEXTURE_MAG_FILTER, DEFAULT_TEXTURE_MAG_FILTER);
		glTextureParameteri(glID, GL_TEXTURE_MIN_FILTER, DEFAULT_TEXTURE_MIN_FILTER);
		glGenerateTextureMipmap(glID);
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
		m_Textures.push_back(glID);
		return glID;
	}

	void Loader::cleanUp()
	{
		for (size_t i = 0; i < m_Vaos1.size(); ++i) {
			delete m_Vaos1[i];
		}
		m_Vaos1.clear();

		for (size_t i = 0; i < m_Textures.size(); ++i) {
			glDeleteTextures(1, &m_Textures[i]);
		}
		m_Textures.clear();
	}

	VertexArray* Loader::createVAO()
	{
		auto va = new VertexArray();
		m_Vaos1.push_back(va);
		return va;
	}

	unsigned int Loader::setupTexture(int width, int height, unsigned char * data, bool alpha)
	{
		unsigned int id = 0;
		glCreateTextures(GL_TEXTURE_2D, 1, &id);
		glBindTexture(GL_TEXTURE_2D, id);
		int internalFormat = GL_RGB8;
		unsigned int ImageFormat = GL_RGB;
		if (alpha) {
			internalFormat = GL_RGBA8;
			ImageFormat = GL_RGBA;
		}
		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, ImageFormat, GL_UNSIGNED_BYTE, data);
		glTextureParameteri(id, GL_TEXTURE_WRAP_S, DEFAULT_TEXTURE_WRAP_S);
		glTextureParameteri(id, GL_TEXTURE_WRAP_T, DEFAULT_TEXTURE_WRAP_T);
		glTextureParameteri(id, GL_TEXTURE_MIN_FILTER, DEFAULT_TEXTURE_MIN_FILTER);
		glTextureParameteri(id, GL_TEXTURE_MAG_FILTER, DEFAULT_TEXTURE_MAG_FILTER);
		glGenerateTextureMipmap(id);
		glBindTexture(GL_TEXTURE_2D, 0);
		return id;
	}
} }

