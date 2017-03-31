#include "water_frame_buffer.h"

namespace sloth { namespace graphics {

	WaterFrameBuffer::WaterFrameBuffer()
	{
		// initialize reflection
		m_Reflection = new FrameBuffer(WATER_REFLECTION_WIDTH, WATER_REFLECTION_HEIGHT);
		m_Reflection->addColorTextureAttachment(0);
		m_Reflection->addDepthRenderBufferAttachment();
		// initialize refraction
		m_Refraction = new FrameBuffer(WATER_REFLECTION_WIDTH, WATER_REFLECTION_HEIGHT);
		m_Refraction->addColorTextureAttachment(0);
		m_Refraction->addDepthTextureAttachment();
		// m_Refraction->addDepthRenderBufferAttachment(WATER_REFRACTION_WIDTH, WATER_REFRACTION_HEIGHT);
	}

	WaterFrameBuffer::~WaterFrameBuffer()
	{
		delete m_Reflection;
		delete m_Refraction;
	}

	void WaterFrameBuffer::bindReflectionFrameBuffer()
	{
		m_Reflection->bind();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		m_Reflection->setDrawBuffer(0);
	}

	void WaterFrameBuffer::bindRefractionFrameBuffer()
	{
		m_Refraction->bind();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		m_Reflection->setDrawBuffer(0);
	}

	void WaterFrameBuffer::unbind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glViewport(0, 0, Input::windowWidth, Input::windowHeight);
	}

} }
