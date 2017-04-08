/************************************************************************ 
 * @project 	:  sloth
 * @class   	:  FrameBuffer
 * @version 	:  v1.0.0
 * @description :  ��װ OpenGL ֡����
 * @author		:  Oscar Shen
 * @creat 		:  2017��2��16��10:45:25
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
		* @description	: ���һ����ɫ������
		* @author		: Oscar Shen
		* @creat		: 2017��2��16��10:42:32
		***********************************************************************/
		void addColorTextureAttachment(unsigned int index);

		/************************************************************************
		* @description	: ���һ����ɫ��Ⱦ���帽�������������ز�����������Ϊ 4
		* @author		: Oscar Shen
		* @creat		: 2017��3��31��11:05:13
		***********************************************************************/
		void addColorRenderBufferAttachment(unsigned int index);

		/************************************************************************
		* @description	:���һ�����������
		* @author		: Oscar Shen
		* @creat		: 2017��2��16��10:42:50
		***********************************************************************/
		void addDepthTextureAttachment();

		/************************************************************************
		* @description	: ���һ����Ⱦ���帽��
		* @author		: Oscar Shen
		* @creat		: 2017��2��16��10:43:07
		***********************************************************************/
		void addDepthRenderBufferAttachment();

		/************************************************************************
		* @description	: �� frame buffer
		* @author		: Oscar Shen
		* @creat		: 2017��2��16��10:43:29
		***********************************************************************/
		void bind();

		/************************************************************************
		* @description	: �ָ�Ĭ�� frame buffer
		* @author		: Oscar Shen
		* @creat		: 2017��2��16��10:43:50
		***********************************************************************/
		void unbind();

		/************************************************************************
		* @description	: ���õ�ǰ��Ҫд��Ļ�������
		* @author		: Oscar Shen
		* @creat		: 2017��2��16��10:44:26
		***********************************************************************/
		void setDrawBuffer(unsigned int index);

		/************************************************************************
		* @description	: ���õ�ǰ��Ҫ��ȡ�Ļ�������
		* @author		: Oscar Shen
		* @creat		: 2017��4��8��23:14:16
		***********************************************************************/
		void setReadBuffer(unsigned int index);

		/************************************************************************
		* @description	: ���� frame buffer ����ת������һ�� frame buffer
		* @author		: Oscar Shen
		* @creat		: 2017��3��31��14:44:31
		***********************************************************************/
		void resolveToFrameBuffer(FrameBuffer &outputFrameBuffer);

		/************************************************************************
		* @description	: ���� frame buffer ����ת������һ�� frame buffer
		* @author		: Oscar Shen
		* @creat		: 2017��3��31��14:44:31
		***********************************************************************/
		void resolveToScreen();

		/************************************************************************
		* @description	: ��յ�ǰ frame buffer �����Ѿ����ص���Դ
		* @author		: Oscar Shen
		* @creat		: 2017��2��16��10:44:57
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
