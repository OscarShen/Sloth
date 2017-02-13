#include "texture_manager_2d.h"

namespace sloth { namespace graphics {

	TextureManager2D* TextureManager2D::m_Inst(nullptr);

	TextureManager2D* TextureManager2D::inst()
	{
		if (!m_Inst)
			m_Inst = new TextureManager2D();
		return m_Inst;
	}

	TextureManager2D::~TextureManager2D()
	{
		unloadAllTextures();
		m_Inst = nullptr;
	}

	void TextureManager2D::loadCubeMap(unsigned int cubeMapID, const std::vector<std::string>& cubeMapPaths, bool alpha, unsigned int mipmap)
	{
		auto cubeMap = new TextureCubeMap();
		// 重复就先删除已有的
		if (m_CubeMaps.find(cubeMapID) != m_CubeMaps.end()) { unloadCubeMap(cubeMapID); }
		unsigned int glID = 0;
		glCreateTextures(GL_TEXTURE_CUBE_MAP, 1, &glID);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, glID);
		if (alpha)
		{
			cubeMap->setInternalFormat(GL_RGBA8);
			cubeMap->setImageFormat(GL_RGBA);
		}
		cubeMap->setMipmap(mipmap);
		int width, height;
		for (size_t i = 0; i < cubeMapPaths.size(); ++i) {
			unsigned char* image = SOIL_load_image(cubeMapPaths[i].c_str(),
				&width, &height, 0, alpha ? SOIL_LOAD_RGBA : SOIL_LOAD_RGB);
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, cubeMap->getMipmap(), cubeMap->getInternalFormat(),
				width, height, 0, cubeMap->getImageFormat(), GL_UNSIGNED_BYTE, image);
			SOIL_free_image_data(image);
		}
		glTextureParameteri(glID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTextureParameteri(glID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		cubeMap->setID(glID);
		cubeMap->setWidth(width);
		cubeMap->setHeight(height);
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
		m_CubeMaps[cubeMapID] = cubeMap;
	}

	void TextureManager2D::unloadCubeMap(unsigned int cubeMapID)
	{
		if (m_CubeMaps.find(cubeMapID) != m_CubeMaps.end())
		{
			unsigned int glID = m_CubeMaps[cubeMapID]->getID();
			glDeleteTextures(1, &glID);
			delete m_CubeMaps[cubeMapID];
			m_CubeMaps.erase(cubeMapID);
		}
	}

	void TextureManager2D::unloadAllCubeMap()
	{
		auto i = m_CubeMaps.begin();

		while (i != m_CubeMaps.end())
		{
			auto j = i;
			i++;
			unloadCubeMap(j->first);
		}
		m_CubeMaps.clear();
	}

	void TextureManager2D::bindCubeMap(unsigned int cubeMapID)
	{
		if (m_CubeMaps.find(cubeMapID) != m_CubeMaps.end())
			glBindTexture(GL_TEXTURE_CUBE_MAP, m_CubeMaps[cubeMapID]->getID());
	}

	void TextureManager2D::unbindCubeMap()
	{
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	}

	void TextureManager2D::loadTexture(const unsigned int texID, const char *file, bool alpha, unsigned int mipmap)
	{
		if (m_texID.find(texID) != m_texID.end())
			unloadTexture(texID);
		m_texID[texID] = loadTextureFromFile(file, alpha, mipmap);
	}

	bool TextureManager2D::unloadTexture(const unsigned int texID)
	{
		bool result(true);
		//if this texture ID mapped, unload it's texture, and remove it from the map
		if (m_texID.find(texID) != m_texID.end())
		{
			glDeleteTextures(1, &m_texID[texID]->m_ID);
			delete m_texID[texID];
			m_texID.erase(texID);
		}
		//otherwise, unload failed
		else
		{
			result = false;
		}

		return result;
	}

	bool TextureManager2D::bindTexture(const unsigned int texID)
	{
		bool result(true);
		//if this texture ID mapped, bind it's texture as current
		if (m_texID.find(texID) != m_texID.end())
			glBindTexture(GL_TEXTURE_2D, m_texID[texID]->getID());
		//otherwise, binding failed
		else
			result = false;

		return result;
	}

	bool TextureManager2D::unbindTexture()
	{
		bool result(true);
		glBindTexture(GL_TEXTURE_2D, 0);
		return result;
	}

	void TextureManager2D::unloadAllTextures()
	{
		//start at the begginning of the texture map
		auto i = m_texID.begin();

		//Unload the textures untill the end of the texture map is found
		while (i != m_texID.end())
		{
			auto j = i;
			i++;
			unloadTexture(j->first);
		}

		m_texID.clear();
	}

	bool TextureManager2D::activateTexUnit(const unsigned int index)
	{
		glActiveTexture(GL_TEXTURE0 + index);
		return true;
	}

	Texture2D * TextureManager2D::getTexture(const unsigned int texID)
	{
		Texture2D * result(nullptr);
		if (m_texID.find(texID) != m_texID.end())
			result = m_texID[texID];
		return result;
	}

	Texture2D* TextureManager2D::loadTextureFromFile(const GLchar * file, GLboolean alpha, GLuint mipmap)
	{
		// Create Texture object
		Texture2D *texture = new Texture2D();
		if (alpha)
		{
			texture->m_InternalFormat = GL_RGBA8;
			texture->m_ImageFormat = GL_RGBA;
		}
		// Load image
		int width, height;
		unsigned char* image = SOIL_load_image(file, &width, &height, 0, texture->m_ImageFormat == GL_RGBA ? SOIL_LOAD_RGBA : SOIL_LOAD_RGB);
		// Now generate texture
		texture->generate(width, height, image, mipmap);
		// And finally free image data
		SOIL_free_image_data(image);
		return texture;
	}

} }