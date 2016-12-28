#include "texture_2d.h"
#include "../../utils/error_check.h"

namespace sloth { namespace graphics {

	Texture2D::Texture2D()
		:m_Width(0), m_Height(0), m_InternalFormat(GL_RGB8), m_ImageFormat(GL_RGB), m_Mipmap(0),
		m_Wrap_S(GL_REPEAT), m_Wrap_T(GL_REPEAT), m_Filter_Min(GL_LINEAR), m_Filter_Max(GL_LINEAR)
	{}

	void Texture2D::generate(GLuint width, GLuint height, unsigned char * data, GLuint mipmap)
	{
		m_Width = width;
		m_Height = height;
		m_Mipmap = mipmap;
		glCreateTextures(GL_TEXTURE_2D, 1, &m_ID);
		glTextureStorage2D(m_ID, mipmap + 1, m_InternalFormat, width, height);
		glTextureSubImage2D(m_ID, 0, 0, 0, width, height, m_ImageFormat, GL_UNSIGNED_BYTE, data);
		glTextureParameteri(m_ID, GL_TEXTURE_WRAP_S, m_Wrap_S);
		glTextureParameteri(m_ID, GL_TEXTURE_WRAP_T, m_Wrap_T);
		glTextureParameteri(m_ID, GL_TEXTURE_MIN_FILTER, m_Filter_Min);
		glTextureParameteri(m_ID, GL_TEXTURE_MAG_FILTER, m_Filter_Max);
		glGenerateTextureMipmap(m_ID);
	}

	void Texture2D::bind() const
	{
		glBindTexture(GL_TEXTURE_2D, m_ID);
	}

	void Texture2D::unbind() const
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void Texture2D::setWrapS(GLint param)
	{
		glTextureParameteri(m_ID, GL_TEXTURE_WRAP_S, param);
		m_Wrap_S = param;
	}

	void Texture2D::setWrapT(GLint param)
	{
		glTextureParameteri(m_ID, GL_TEXTURE_WRAP_T, param);
		m_Wrap_T = param;
	}

	void Texture2D::setFilterMin(GLint param)
	{
		glTextureParameteri(m_ID, GL_TEXTURE_MIN_FILTER, param);
		m_Filter_Min = param;
	}

	void Texture2D::setFilterMag(GLint param)
	{
		glTextureParameteri(m_ID, GL_TEXTURE_MAG_FILTER, param);
		m_Filter_Max = param;
	}

} }
