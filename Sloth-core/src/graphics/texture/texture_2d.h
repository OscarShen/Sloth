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

		float m_Shininess; // Shaniness
		float m_Reflectivity; // Reflectivity

		bool m_HasTransparency = false;
		bool m_UseFakeLighting = false;
	public:
		// Constructor (sets default texture modes)
		constexpr Texture2D()
			:m_ID(0), m_Width(0), m_Height(0), m_InternalFormat(GL_RGB8), m_ImageFormat(GL_RGB), m_Mipmap(0),
			m_Wrap_S(GL_REPEAT), m_Wrap_T(GL_REPEAT), m_Filter_Min(GL_LINEAR), m_Filter_Max(GL_LINEAR),
			m_Shininess(128.0f), m_Reflectivity(1.0f) {}

		void generate(GLuint width, GLuint height, unsigned char* data, GLuint mipmap = 0);
		// Binds the texture as the current active GL_TEXTURE_2D texture object
		void bind() const;
		void unbind() const;

		// Setters and getters
		inline GLuint getID() { return m_ID; }
		inline GLuint getWidth() { return m_Width; }
		inline GLuint getHeight() { return m_Height; }
		inline GLuint getInternalFormat() const { return m_InternalFormat; }
		inline GLuint getImageFormat() const { return m_ImageFormat; }
		inline GLint getWrapS() const { return m_Wrap_S; }
		inline GLint getWrapT() const { return m_Wrap_T; }
		inline float getShininess() const{ return m_Shininess; }
		inline float getReflectivity() const { return m_Reflectivity; }
		inline GLint getFilterMinParam() const { return m_Filter_Min; }
		inline GLint getFilterMagParam() const { return m_Filter_Max; }
		inline bool hasTransparency() const { return m_HasTransparency; }
		inline bool isUseFakeLighting() const { return m_UseFakeLighting; }

		void setWrapS(GLint param);
		void setWrapT(GLint param);
		void setFilterMin(GLint param);
		void setFilterMag(GLint param);
		void setShininess(float shininess) { m_Shininess = shininess; }
		void setReflectivity(float reflectivity) { m_Reflectivity = reflectivity; }
		void setTransparency(bool hasTransparency) { m_HasTransparency = hasTransparency; }
		void setUseFakeLighting(bool useFakeLighting) { m_UseFakeLighting = useFakeLighting; }

		friend TextureManager2D;
	};

} }
#endif // !SLOTH_TEXTURE_2D_H_
