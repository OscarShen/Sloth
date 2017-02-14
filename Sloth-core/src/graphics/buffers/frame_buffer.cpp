#include "frame_buffer.h"

namespace sloth { namespace graphics {
	FrameBuffer::FrameBuffer()
	{
		glCreateFramebuffers(1, &m_ID);
		glNamedFramebufferDrawBuffer(m_ID, GL_COLOR_ATTACHMENT0);
	}

	FrameBuffer::~FrameBuffer()
	{
		cleanUp();
		glDeleteFramebuffers(1, &m_ID);
	}

	void FrameBuffer::addColorAttachment(unsigned int texID, unsigned int index, unsigned int width, unsigned int height)
	{
		auto tm = TextureManager2D::inst();
		unsigned int id;
		glCreateTextures(GL_TEXTURE_2D, 1, &id);
		glTextureStorage2D(id, 1, GL_RGB8, width, height);
		glTextureParameteri(id, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTextureParameteri(id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glNamedFramebufferTexture(m_ID, GL_COLOR_ATTACHMENT0 + index, id, 0);
		if (m_TextureAttachment.size() < index + 1) {
			unsigned int margin = index + 1 - m_TextureAttachment.size();
			for (unsigned int i = 0; i < margin; ++i)
				m_TextureAttachment.push_back(0);
		}
		// 如果位置上已经有color attachment，则覆盖并删除
		if (m_TextureAttachment[index] != 0) {
			// TODO! Add to log
			tm->unloadTexture(m_TextureAttachment[index]);
		}
		m_TextureAttachment[index] = texID;

		tm->submitInternalTexture(texID, id);
	}

	void FrameBuffer::addDepthTextureAttachment(unsigned int texID, unsigned int width, unsigned int height)
	{
		unsigned int id;
		glCreateTextures(GL_TEXTURE_2D, 1, &id);
		glTextureStorage2D(id, 1, GL_RGB8, width, height);
		glTextureParameteri(id, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTextureParameteri(id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glNamedFramebufferTexture(m_ID, GL_DEPTH_ATTACHMENT, id, 0);
		// 如果已经有depth attachment，则覆盖并删除
		if (m_DepthTextureAttachment != 0) {
			// TODO! Add to log
			glDeleteTextures(1, &m_DepthTextureAttachment);
		}
		m_DepthTextureAttachment = id;
	}

	void FrameBuffer::addDepthRenderBufferAttachment(unsigned int width, unsigned int height)
	{
		unsigned int id;
		glCreateRenderbuffers(1, &id);
		glNamedRenderbufferStorage(id, GL_DEPTH_COMPONENT32, width, height);
		glNamedFramebufferRenderbuffer(m_ID, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, id);
		// 如果已经存在，则覆盖并删除
		if (m_DepthRenderBufferAttachment != 0) {
			// TODO! Add to log
			glDeleteTextures(1, &m_DepthRenderBufferAttachment);
		}
		m_DepthRenderBufferAttachment = id;
	}

	void FrameBuffer::bind(unsigned int width, unsigned int height)
	{
		// 保证 gl_texture_2d 没有绑定
		glBindTexture(GL_TEXTURE_2D, 0);
		glBindFramebuffer(GL_FRAMEBUFFER, m_ID);
		glViewport(0, 0, width, height);
	}

	void FrameBuffer::unbind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	}

	void FrameBuffer::setDrawBuffer(unsigned int index)
	{
		glNamedFramebufferDrawBuffer(m_ID, GL_COLOR_ATTACHMENT0 + index);
	}

	void FrameBuffer::cleanUp()
	{
		auto tm = TextureManager2D::inst();
		for (unsigned int i = 0; i < m_TextureAttachment.size(); ++i) {
			if (m_TextureAttachment[i] != 0) {
				unsigned int texID = tm->queryTexID(m_TextureAttachment[i]);
				tm->unloadTexture(texID);
			}
		}
		m_TextureAttachment.clear();

		if (m_DepthTextureAttachment != 0) {
			unsigned int texID = tm->queryTexID(m_DepthTextureAttachment);
			tm->unloadTexture(texID);
		}
		m_DepthTextureAttachment = 0;

		if (m_DepthRenderBufferAttachment != 0)
			glDeleteRenderbuffers(1, &m_DepthRenderBufferAttachment);
		m_DepthRenderBufferAttachment = 0;
	}

} }
