#pragma once
#ifndef SLOTH_TEXTURE_2D_H_
#define SLOTH_TEXTURE_2D_H_

#include "texture_manager_2d.h"
namespace sloth { namespace graphics {
	class TextureManager2D;
	class Texture2D
	{
	protected:
		GLuint m_ID;
		GLuint m_Width, m_Height; // Width and height of loaded image in pixels
		// Texture format
		GLuint m_InternalFormat; // Format of texture object
		GLuint m_ImageFormat; // Format of loaded image
		// Texture configuration
		GLuint m_Wrap_S; // Wrapping mode on S axis
		GLuint m_Wrap_T; // Wrapping mode on T axis
		GLuint m_Filter_Min; // Filtering mode if texture pixels < screen pixels
		GLuint m_Filter_Max; // Filtering mode if texture pixels > screen pixels
		GLuint m_Mipmap; // Mipmap levels
	public:
		// Constructor (sets default texture modes)
		Texture2D();

		void generate(GLuint width, GLuint height, unsigned char* data, GLuint mipmap = 0);
		// Binds the texture as the current active GL_TEXTURE_2D texture object
		void bind() const;
		void unbind() const;

		// Setters and getters
		inline GLuint getID() { return m_ID; }
		inline GLuint getWidth() { return m_Width; }
		inline GLuint getHeight() { return m_Height; }
		inline const GLuint getInternalFormat() const { return m_InternalFormat; }
		inline const GLuint getImageFormat() const { return m_ImageFormat; }
		inline const GLint getWrapS() const { return m_Wrap_S; }
		inline const GLint getWrapT() const { return m_Wrap_T; }
		void setWrapS(GLint param);
		void setWrapT(GLint param);
		inline const GLint getFilterMinParam() const { return m_Filter_Min; }
		inline const GLint getFilterMagParam() const { return m_Filter_Max; }
		void setFilterMin(GLint param);
		void setFilterMag(GLint param);

		friend TextureManager2D;
	};

} }
#endif // !SLOTH_TEXTURE_2D_H_
