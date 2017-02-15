/************************************************************************ 
 * @project 	:  $rootnamespace$
 * @class   	:  $safeitemrootname$
 * @version 	:  v1.0.0
 * @description :  
 * @author		:  $username$
 * @creat 		:  $time$
 * @revise 		:  $time$
************************************************************************ 
 * Copyright @ OscarShen 2017. All rights reserved. 
************************************************************************/  
#pragma once
#ifndef SLOTH_FRAME_BUFFER_H_
#define SLOTH_FRAME_BUFFER_H_

#include <GL/glew.h>
#include <vector>
#include "../../config/macro.h"
namespace sloth { namespace graphics {

	class FrameBuffer
	{
	private:
		unsigned int m_ID;

		std::vector<unsigned int> m_TextureAttachment;

		unsigned int m_DepthTextureAttachment = 0;

		unsigned int m_DepthRenderBufferAttachment = 0;

	public:
		FrameBuffer();

		~FrameBuffer();

		void addColorAttachment(unsigned int index, unsigned int width, unsigned int height);

		void addDepthTextureAttachment(unsigned int width, unsigned int height);

		void addDepthRenderBufferAttachment(unsigned int width, unsigned int height);

		void bind(unsigned int width, unsigned int height);

		void unbind();

		void setDrawBuffer(unsigned int index);

		void cleanUp();

		inline unsigned int getColorTexture(unsigned int index) const { return m_TextureAttachment[index]; }

		inline unsigned int getDepthTexture() const { return m_DepthTextureAttachment; }

		inline unsigned int getDepthRenderBuffer() const { return m_DepthRenderBufferAttachment; }
	};

} }



#endif // !SLOTH_FRAME_BUFFER_H_
