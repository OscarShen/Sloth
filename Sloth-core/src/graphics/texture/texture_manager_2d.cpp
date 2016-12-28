#include "texture_manager_2d.h"

namespace sloth { namespace graphics {

	TextureManager2D* TextureManager2D::m_inst(nullptr);

	TextureManager2D* TextureManager2D::inst()
	{
		if (!m_inst)
			m_inst = new TextureManager2D();
		return m_inst;
	}

	TextureManager2D::~TextureManager2D()
	{
		unloadAllTextures();
		m_inst = nullptr;
	}

	void TextureManager2D::loadTexture(const unsigned int texID, const GLchar * file, GLboolean alpha, GLuint mipmap)
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

		//clear the texture map
		m_texID.clear();
	}

	bool TextureManager2D::activateTexUnit(const unsigned int index)
	{
		glActiveTexture(GL_TEXTURE0);
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