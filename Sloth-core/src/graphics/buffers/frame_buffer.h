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

		std::vector<unsigned int> m_ColorAttachment;

		unsigned int m_DepthTextureAttachment = 0;

		unsigned int m_DepthRenderBufferAttachment = 0;

	public:
		FrameBuffer();

		~FrameBuffer();

		/************************************************************************
		* @description	: 添加一个颜色纹理附件
		* @author		: Oscar Shen
		* @creat		: 2017年2月16日10:42:32
		***********************************************************************/
		void addColorAttachment(unsigned int index, unsigned int width, unsigned int height);

		/************************************************************************
		* @description	:添加一个深度纹理附件
		* @author		: Oscar Shen
		* @creat		: 2017年2月16日10:42:50
		***********************************************************************/
		void addDepthTextureAttachment(unsigned int width, unsigned int height);

		/************************************************************************
		* @description	: 添加一个渲染缓冲附件
		* @author		: Oscar Shen
		* @creat		: 2017年2月16日10:43:07
		***********************************************************************/
		void addDepthRenderBufferAttachment(unsigned int width, unsigned int height);

		/************************************************************************
		* @description	: 绑定 frame buffer，需要输入 width 和 height
		* @author		: Oscar Shen
		* @creat		: 2017年2月16日10:43:29
		***********************************************************************/
		void bind(unsigned int width, unsigned int height);

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
		* @description	: 清空当前 frame buffer 所有已经加载的资源
		* @author		: Oscar Shen
		* @creat		: 2017年2月16日10:44:57
		***********************************************************************/
		void cleanUp();

		inline unsigned int getColorTexture(unsigned int index) const { return m_ColorAttachment[index]; }

		inline unsigned int getDepthTexture() const { return m_DepthTextureAttachment; }

		inline unsigned int getDepthRenderBuffer() const { return m_DepthRenderBufferAttachment; }
	};

} }



#endif // !SLOTH_FRAME_BUFFER_H_
