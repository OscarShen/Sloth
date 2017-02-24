#include "water_frame_buffer.h"

namespace sloth { namespace graphics {

	WaterFrameBuffer::WaterFrameBuffer()
	{
		// initialize reflection
		m_Reflection = new FrameBuffer();
		m_Reflection->addColorAttachment(0, WATER_REFLECTION_WIDTH, WATER_REFLECTION_HEIGHT);
		m_Reflection->addDepthRenderBufferAttachment(WATER_REFLECTION_WIDTH, WATER_REFLECTION_HEIGHT);
		// initialize refraction
		m_Refraction = new FrameBuffer();
		m_Refraction->addColorAttachment(0, WATER_REFRACTION_WIDTH, WATER_REFRACTION_HEIGHT);
		m_Refraction->addDepthTextureAttachment(WATER_REFRACTION_WIDTH, WATER_REFRACTION_HEIGHT);
		// m_Refraction->addDepthRenderBufferAttachment(WATER_REFRACTION_WIDTH, WATER_REFRACTION_HEIGHT);
	}

	WaterFrameBuffer::~WaterFrameBuffer()
	{
		delete m_Reflection;
		delete m_Refraction;
	}

	void WaterFrameBuffer::bindReflectionFrameBuffer()
	{
		m_Reflection->bind(WATER_REFLECTION_WIDTH, WATER_REFLECTION_HEIGHT);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		m_Reflection->setDrawBuffer(0);
	}

	void WaterFrameBuffer::bindRefractionFrameBuffer()
	{
		m_Refraction->bind(WATER_REFRACTION_WIDTH, WATER_REFRACTION_HEIGHT);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		m_Reflection->setDrawBuffer(0);
	}

	void WaterFrameBuffer::unbind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glViewport(0, 0, Input::windowWidth, Input::windowHeight);
	}

} }
