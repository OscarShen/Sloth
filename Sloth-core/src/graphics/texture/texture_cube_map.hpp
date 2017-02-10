/************************************************************************ 
 * @project 	:  sloth
 * @class   	:  TextureCubeMap
 * @version 	:  v1.0.0
 * @description :  封装了 CubeMap 需要的属性
 * @author		:  Oscar Shen
 * @creat 		:  2017年2月10日11:41:55
 * @revise 		:  
************************************************************************ 
 * Copyright @ OscarShen 2017. All rights reserved. 
************************************************************************/  
#pragma once
#ifndef SLOTH_TEXTURE_CUBE_MAP_H_
#define SLOTH_TEXTURE_CUBE_MAP_H_

#include <GL/glew.h>
#include <vector>
#include <string>

namespace sloth { namespace graphics {

	class TextureCubeMap
	{
	private:
		unsigned int m_ID;
		unsigned int m_Width, m_Height; // Width and height of loaded image in pixels
		// OpenGL 存储格式和图片格式
		unsigned int m_InternalFormat; // Format of texture object
		unsigned int m_ImageFormat; // Format of loaded image
		
		unsigned int m_Filter_Min; // Filtering mode if texture pixels < screen pixels
		unsigned int m_Filter_Mag; // Filtering mode if texture pixels > screen pixels

		unsigned int m_Mipmap;

	public:
		/************************************************************************
		* @description	: 设置默认参数
		* @author		: Oscar Shen
		* @creat		: 2017年2月10日12:05:07
		***********************************************************************/
		constexpr TextureCubeMap()
			:m_ID(0), m_Width(0), m_Height(0), m_InternalFormat(GL_RGB8), m_ImageFormat(GL_RGB), 
			m_Filter_Min(GL_LINEAR), m_Filter_Mag(GL_LINEAR), m_Mipmap(0) {}
		
		inline unsigned int getID() const { return m_ID; }
		void setID(unsigned int glID) { m_ID = glID; }

		inline unsigned int getWidth() const { return m_Width; }
		void setWidth(unsigned int width) { m_Width = width; }

		inline unsigned int getHeight() const { return m_Height; }
		void setHeight(unsigned int height) { m_Height = height; }

		inline unsigned int getInternalFormat() const { return m_InternalFormat; }
		void setInternalFormat(unsigned int internalFormat) { m_InternalFormat = internalFormat; }

		inline unsigned int getImageFormat() const { return m_ImageFormat; }
		void setImageFormat(unsigned int imageFormat) { m_ImageFormat = imageFormat; }

		inline unsigned int getFilterMin() const { return m_Filter_Min; }
		void setFilterMin(unsigned int filterMin) {
			m_Filter_Min = filterMin;
		}

		inline unsigned int getFilterMag() const { return m_Filter_Mag; }
		void setFilterMag(unsigned int filterMag) { m_Filter_Mag = filterMag; }

		inline unsigned int getMipmap() const { return m_Mipmap; }
		void setMipmap(unsigned int mipmapLevel) { m_Mipmap = mipmapLevel; }
	};

} }

#endif // !SLOTH_TEXTURE_CUBE_MAP_H_
