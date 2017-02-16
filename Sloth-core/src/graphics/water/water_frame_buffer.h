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
#ifndef SLOTH_WATER_FRAME_BUFFER_H_
#define SLOTH_WATER_FRAME_BUFFER_H_

#include "../buffers/frame_buffer.h"
#include "../../config/macro.h"
namespace sloth { namespace graphics {

	class WaterFrameBuffer
	{
	private:
		// �������ʹ�õ�֡����
		FrameBuffer *m_Reflection;
		// �������ʹ�õ�֡����
		FrameBuffer *m_Refraction;

	public:
		WaterFrameBuffer();
		~WaterFrameBuffer();

		void bindReflectionFrameBuffer();

		void bindRefractionFrameBuffer();

		void unbind();

		inline unsigned int getReflectionTexture() const { return m_Reflection->getColorTexture(0); }

		inline unsigned int getRefractionTexture() const { return m_Refraction->getColorTexture(0); }

		inline unsigned int getRefractionDepthTexture() const { return m_Refraction->getDepthTexture(); }
	};

} }



#endif // !SLOTH_WATER_FRAME_BUFFER_H_
