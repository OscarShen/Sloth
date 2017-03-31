#include "frame_buffer.h"
#include "../../utils/error_check.h"

namespace sloth { namespace graphics {

	FrameBuffer::FrameBuffer(int width, int height)
		:m_Width(width), m_Height(height)
	{
		glCreateFramebuffers(1, &m_ID);
	}

	FrameBuffer::FrameBuffer(int width, int height, bool multiSample)
		: m_Width(width), m_Height(height), m_MultiSample(multiSample)
	{
		glCreateFramebuffers(1, &m_ID);
	}

	FrameBuffer::~FrameBuffer()
	{
		cleanUp();
		glDeleteFramebuffers(1, &m_ID);
	}

	void FrameBuffer::addColorTextureAttachment(unsigned int index)
	{
		unsigned int id;
		glCreateTextures(GL_TEXTURE_2D, 1, &id);
		glTextureStorage2D(id, 1, GL_RGB8, m_Width, m_Height);
		glTextureParameteri(id, GL_TEXTURE_MAG_FILTER, DEFAULT_TEXTURE_MAG_FILTER);
		glTextureParameteri(id, GL_TEXTURE_MIN_FILTER, DEFAULT_TEXTURE_MIN_FILTER);
		glNamedFramebufferTexture(m_ID, GL_COLOR_ATTACHMENT0 + index, id, 0);
		// 防止空间不足
		while (m_ColorTextureAttachment.size() < index + 1)
			m_ColorTextureAttachment.push_back(0);
		while (m_ColorRenderBufferAttachment.size() < index + 1)
			m_ColorRenderBufferAttachment.push_back(0);
		// 如果位置上已经有color attachment，则覆盖并删除
		if (m_ColorTextureAttachment[index] != 0) {
			glDeleteTextures(1, &m_ColorTextureAttachment[index]);
		}
		if (m_ColorRenderBufferAttachment[index] != 0) {
			glDeleteRenderbuffers(1, &m_ColorRenderBufferAttachment[index]);
		}
		m_ColorTextureAttachment[index] = id;
		m_ColorRenderBufferAttachment[index] = 0;
	}

	void FrameBuffer::addColorRenderBufferAttachment(unsigned int index)
	{
		unsigned int id;
		glCreateRenderbuffers(1, &id);
		if (m_MultiSample) {
			glNamedRenderbufferStorageMultisample(id, 4, GL_RGB8, m_Width, m_Height);
		}
		else {
			glNamedRenderbufferStorage(id, GL_RGB8, m_Width, m_Height);
		}
		glNamedFramebufferRenderbuffer(m_ID, GL_COLOR_ATTACHMENT0 + index, GL_RENDERBUFFER, id);
		// 防止空间不足
		while (m_ColorTextureAttachment.size() < index + 1)
			m_ColorTextureAttachment.push_back(0);
		while (m_ColorRenderBufferAttachment.size() < index + 1)
			m_ColorRenderBufferAttachment.push_back(0);
		// 如果位置上已经有color attachment，则覆盖并删除
		if (m_ColorTextureAttachment[index] != 0) {
			glDeleteTextures(1, &m_ColorTextureAttachment[index]);
		}
		if (m_ColorRenderBufferAttachment[index] != 0) {
			glDeleteRenderbuffers(1, &m_ColorRenderBufferAttachment[index]);
		}
		m_ColorRenderBufferAttachment[index] = id;
		m_ColorTextureAttachment[index] = 0;
	}

	void FrameBuffer::addDepthTextureAttachment()
	{
		unsigned int id;
		glCreateTextures(GL_TEXTURE_2D, 1, &id);
		glTextureStorage2D(id, 1, GL_DEPTH_COMPONENT32, m_Width, m_Height);
		glTextureParameteri(id, GL_TEXTURE_MAG_FILTER, DEFAULT_TEXTURE_MAG_FILTER);
		glTextureParameteri(id, GL_TEXTURE_MIN_FILTER, DEFAULT_TEXTURE_MIN_FILTER);
		glNamedFramebufferTexture(m_ID, GL_DEPTH_ATTACHMENT, id, 0);
		// 如果已经有depth attachment，则覆盖并删除
		if (m_DepthTextureAttachment != 0) {
			// TODO! Add to log
			glDeleteTextures(1, &m_DepthTextureAttachment);
		}
		m_DepthTextureAttachment = id;
	}

	void FrameBuffer::addDepthRenderBufferAttachment()
	{
		unsigned int id;
		glCreateRenderbuffers(1, &id);
		if (m_MultiSample) {
			glNamedRenderbufferStorageMultisample(id, 4, GL_DEPTH_COMPONENT32, m_Width, m_Height);
		}
		else {
			glNamedRenderbufferStorage(id, GL_DEPTH_COMPONENT32, m_Width, m_Height);
		}
		glNamedFramebufferRenderbuffer(m_ID, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, id);
		// 如果已经存在，则覆盖并删除
		if (m_DepthRenderBufferAttachment != 0) {
			// TODO! Add to log
			glDeleteRenderbuffers(1, &m_DepthRenderBufferAttachment);
		}
		m_DepthRenderBufferAttachment = id;
	}

	void FrameBuffer::bind()
	{
		// 保证 gl_texture_2d 没有绑定
		glBindTexture(GL_TEXTURE_2D, 0);
		glBindFramebuffer(GL_FRAMEBUFFER, m_ID);
		glViewport(0, 0, m_Width, m_Height);
	}

	void FrameBuffer::unbind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glViewport(0, 0, Input::windowWidth, Input::windowHeight);
	}

	void FrameBuffer::setDrawBuffer(unsigned int index)
	{
		glNamedFramebufferDrawBuffer(m_ID, GL_COLOR_ATTACHMENT0 + index);
	}

	void FrameBuffer::resolveToFrameBuffer(FrameBuffer & outputFrameBuffer)
	{
		glBlitNamedFramebuffer(m_ID, outputFrameBuffer.m_ID, 0, 0, m_Width, m_Height, 0, 0, outputFrameBuffer.m_Width, outputFrameBuffer.m_Height,
			GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT, GL_NEAREST);
	}

	void FrameBuffer::resolveToScreen()
	{
		glNamedFramebufferDrawBuffer(0, GL_BACK);
		glBlitNamedFramebuffer(m_ID, 0, 0, 0, m_Width, m_Height, 0, 0, Input::windowWidth, Input::windowHeight, GL_COLOR_BUFFER_BIT, GL_NEAREST);
	}

	void FrameBuffer::cleanUp()
	{
		glDeleteTextures(m_ColorTextureAttachment.size(), m_ColorTextureAttachment.data());
		m_ColorTextureAttachment.clear();

		glDeleteRenderbuffers(m_ColorRenderBufferAttachment.size(), m_ColorRenderBufferAttachment.data());

		glDeleteTextures(1, &m_DepthTextureAttachment);
		m_DepthTextureAttachment = 0;

		glDeleteRenderbuffers(1, &m_DepthRenderBufferAttachment);
		m_DepthRenderBufferAttachment = 0;
	}

} }
