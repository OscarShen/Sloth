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

		std::vector<unsigned int> m_ColorAttachment;

		unsigned int m_DepthTextureAttachment = 0;

		unsigned int m_DepthRenderBufferAttachment = 0;

	public:
		FrameBuffer();

		~FrameBuffer();

		/************************************************************************
		* @description	: ���һ����ɫ������
		* @author		: Oscar Shen
		* @creat		: 2017��2��16��10:42:32
		***********************************************************************/
		void addColorAttachment(unsigned int index, unsigned int width, unsigned int height);

		/************************************************************************
		* @description	:���һ�����������
		* @author		: Oscar Shen
		* @creat		: 2017��2��16��10:42:50
		***********************************************************************/
		void addDepthTextureAttachment(unsigned int width, unsigned int height);

		/************************************************************************
		* @description	: ���һ����Ⱦ���帽��
		* @author		: Oscar Shen
		* @creat		: 2017��2��16��10:43:07
		***********************************************************************/
		void addDepthRenderBufferAttachment(unsigned int width, unsigned int height);

		/************************************************************************
		* @description	: �� frame buffer����Ҫ���� width �� height
		* @author		: Oscar Shen
		* @creat		: 2017��2��16��10:43:29
		***********************************************************************/
		void bind(unsigned int width, unsigned int height);

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
		* @description	: ��յ�ǰ frame buffer �����Ѿ����ص���Դ
		* @author		: Oscar Shen
		* @creat		: 2017��2��16��10:44:57
		***********************************************************************/
		void cleanUp();

		inline unsigned int getColorTexture(unsigned int index) const { return m_ColorAttachment[index]; }

		inline unsigned int getDepthTexture() const { return m_DepthTextureAttachment; }

		inline unsigned int getDepthRenderBuffer() const { return m_DepthRenderBufferAttachment; }
	};

} }



#endif // !SLOTH_FRAME_BUFFER_H_
