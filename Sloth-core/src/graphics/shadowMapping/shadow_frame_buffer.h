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
#ifndef SLOTH_SHADOW_FRAME_BUFFER_H_
#define SLOTH_SHADOW_FRAME_BUFFER_H_

#include "../buffers/frame_buffer.h"

namespace sloth { namespace graphics {

	class ShadowFrameBuffer : public FrameBuffer
	{
	private:
		int m_Width;
		int m_Height;

	public:
		ShadowFrameBuffer(int width, int height);

		void bindShadowFrameBuffer();

		unsigned int getShadowMap() { return m_DepthTextureAttachment; }

	private:
		void initialiseFrameBuffer();
	};
} }



#endif // !SLOTH_SHADOW_FRAME_BUFFER_H_
