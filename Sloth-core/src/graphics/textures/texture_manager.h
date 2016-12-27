#pragma once
#ifndef SLOTH_TEXTURE_MANAGER_H_
#define SLOTH_TEXTURE_MANAGER_H_

#include <map>
#include <GL/glew.h>
#include <FreeImage.h>

namespace sloth { namespace graphics {
	class TextureManager
	{
	protected:
		static TextureManager* m_inst;
		std::map<unsigned int, GLuint> m_texID;
	public:
		static TextureManager *inst();
		virtual ~TextureManager();

		//load a texture an make it the current texture
		//if texID is already in use, it will be unloaded and replaced with this texture
		bool loadTexture(const char *filename,	// where to load the file from
			const unsigned int texID,			//arbitrary id you will reference the texture by
												//does not have to be generated with glGenTextures
			GLenum image_format = GL_RGB,		// format the image is in
			GLint internal_format = GL_RGB,		// format to store the image in
			GLint level = 0,					// mipmapping level
			GLint border = 0);					//border size

		// free the memory for a texture
		bool unloadTexture(const unsigned int texID);

		// set the current texture
		bool bindTexture(const unsigned int texID);

		// free all texture memory
		void unloadAllTextures();

		// activate texture unit
		bool activateTexUnit(const unsigned int index);

	protected:
		TextureManager() {}
	};
} }
#endif // !SLOTH_TEXTURE_MANAGER_H_
