#pragma once
#ifndef SLOTH_TEXTURE_MANAGER_H_
#define SLOTH_TEXTURE_MANAGER_H_

#include <map>
#include <GL/glew.h>
#include <SOIL/SOIL.h>
#include "texture_2d.h"

namespace sloth { namespace graphics {
	class Texture2D;
	class TextureManager2D
	{
	protected:
		static TextureManager2D* m_inst;
		std::map<unsigned int, Texture2D*> m_texID;
	public:
		static TextureManager2D *inst();
		virtual ~TextureManager2D();

		// load texture
		void loadTexture(const unsigned int texID, const char *file, bool alpha = false, unsigned int mipmap = 0);

		// set the current texture
		bool bindTexture(const unsigned int texID);

		// unbind any texutre
		bool unbindTexture();

		// free the memory for a texture
		bool unloadTexture(const unsigned int texID);

		// free all texture memory
		void unloadAllTextures();

		// activate texture unit
		bool activateTexUnit(const unsigned int index);

		// return texture pointer of texID
		Texture2D * getTexture(const unsigned int texID);

	protected:
		TextureManager2D() {}

		// Loads a single texture from file
		Texture2D* loadTextureFromFile(const GLchar *file, GLboolean alpha, GLuint mipmap);
	};
} }
#endif // !SLOTH_TEXTURE_MANAGER_H_
