/************************************************************************ 
 * @project 	:  sloth
 * @class   	:  FrameBuffer
 * @version 	:  v1.0.0
 * @description :  封装 OpenGL 帧缓冲
 * @author		:  Oscar Shen
 * @creat 		:  2017年2月16日10:45:25
 * @revise 		:  
************************************************************************ 
 * Copyright @ OscarShen 2017. All rights reserved. 
************************************************************************/  
#pragma once
#ifndef SLOTH_FRAME_BUFFER_H_
#define SLOTH_FRAME_BUFFER_H_

#include <GL/glew.h>
#include <vector>
#include "../info/info.h"
#include "../../config/header.hpp"
namespace sloth { namespace graphics {

	class FrameBuffer
	{
	protected:
		unsigned int m_ID;
		int m_Width, m_Height;

		std::vector<unsigned int> m_ColorTextureAttachment;
		std::vector<unsigned int> m_ColorRenderBufferAttachment;

		unsigned int m_DepthTextureAttachment = 0;

		unsigned int m_DepthRenderBufferAttachment = 0;

		bool m_MultiSample = false;

	public:
		FrameBuffer(int width, int height);
		FrameBuffer(int width, int height, bool multiSample);

		~FrameBuffer();

		/************************************************************************
		* @description	: 添加一个颜色纹理附件
		* @author		: Oscar Shen
		* @creat		: 2017年2月16日10:42:32
		***********************************************************************/
		void addColorTextureAttachment(unsigned int index);

		/************************************************************************
		* @description	: 添加一个颜色渲染缓冲附件，若开启多重采样，采样数为 4
		* @author		: Oscar Shen
		* @creat		: 2017年3月31日11:05:13
		***********************************************************************/
		void addColorRenderBufferAttachment(unsigned int index);

		/************************************************************************
		* @description	:添加一个深度纹理附件
		* @author		: Oscar Shen
		* @creat		: 2017年2月16日10:42:50
		***********************************************************************/
		void addDepthTextureAttachment();

		/************************************************************************
		* @description	: 添加一个渲染缓冲附件
		* @author		: Oscar Shen
		* @creat		: 2017年2月16日10:43:07
		***********************************************************************/
		void addDepthRenderBufferAttachment();

		/************************************************************************
		* @description	: 绑定 frame buffer
		* @author		: Oscar Shen
		* @creat		: 2017年2月16日10:43:29
		***********************************************************************/
		void bind();

		/************************************************************************
		* @description	: 恢复默认 frame buffer
		* @author		: Oscar Shen
		* @creat		: 2017年2月16日10:43:50
		***********************************************************************/
		void unbind();

		/************************************************************************
		* @description	: 设置当前需要写入的缓冲纹理
		* @author		: Oscar Shen
		* @creat		: 2017年2月16日10:44:26
		***********************************************************************/
		void setDrawBuffer(unsigned int index);

		/************************************************************************
		* @description	: 设置当前需要读取的缓冲纹理
		* @author		: Oscar Shen
		* @creat		: 2017年4月8日23:14:16
		***********************************************************************/
		void setReadBuffer(unsigned int index);

		/************************************************************************
		* @description	: 将本 frame buffer 内容转换到另一个 frame buffer
		* @author		: Oscar Shen
		* @creat		: 2017年3月31日14:44:31
		***********************************************************************/
		void resolveToFrameBuffer(FrameBuffer &outputFrameBuffer);

		/************************************************************************
		* @description	: 将本 frame buffer 内容转换到另一个 frame buffer
		* @author		: Oscar Shen
		* @creat		: 2017年3月31日14:44:31
		***********************************************************************/
		void resolveToScreen();

		/************************************************************************
		* @description	: 清空当前 frame buffer 所有已经加载的资源
		* @author		: Oscar Shen
		* @creat		: 2017年2月16日10:44:57
		***********************************************************************/
		void cleanUp();
		unsigned int getColorTexture(unsigned int index) const {
			if (m_ColorTextureAttachment[index] == 0)
				std::cout << "color texture not exit in GL_COLOR_ATTACHMENT" << index << std::endl;
			return m_ColorTextureAttachment[index]; 
		}

		unsigned int getColorRenderBuffer(unsigned int index) const {
			if (m_ColorTextureAttachment[index] == 0)
				std::cout << "color render buffer not exit in GL_COLOR_ATTACHMENT" << index << std::endl;
			return m_ColorTextureAttachment[index];
		}

		inline unsigned int getDepthTexture() const { return m_DepthTextureAttachment; }

		inline unsigned int getDepthRenderBuffer() const { return m_DepthRenderBufferAttachment; }
	};

} }



#endif // !SLOTH_FRAME_BUFFER_H_
