#pragma once
#ifndef SLOTH_TEXTURE_MANAGER_H_
#define SLOTH_TEXTURE_MANAGER_H_

#include <map>
#include <GL/glew.h>
#include <SOIL.h>
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
		void loadTexture(const GLchar *file, GLboolean alpha, const unsigned int texID, GLuint mipmap = 0);

		// free the memory for a texture
		bool unloadTexture(const unsigned int texID);


		// set the current texture
		bool bindTexture(const unsigned int texID);

		// free all texture memory
		void unloadAllTextures();

		// activate texture unit
		bool activateTexUnit(const unsigned int index);

	protected:
		TextureManager2D() {}

		// Loads a single texture from file
		Texture2D* loadTextureFromFile(const GLchar *file, GLboolean alpha, GLuint mipmap);
	};
} }
#endif // !SLOTH_TEXTURE_MANAGER_H_
