#include "frame_buffer.h"

namespace sloth { namespace graphics {
	FrameBuffer::FrameBuffer()
	{
		glCreateFramebuffers(1, &m_ID);
	}

	FrameBuffer::~FrameBuffer()
	{
		cleanUp();
		glDeleteFramebuffers(1, &m_ID);
	}

	void FrameBuffer::addColorAttachment(unsigned int index, unsigned int width, unsigned int height)
	{
		unsigned int id;
		glCreateTextures(GL_TEXTURE_2D, 1, &id);
		glTextureStorage2D(id, 1, GL_RGB8, width, height);
		glTextureParameteri(id, GL_TEXTURE_MAG_FILTER, DEFAULT_TEXTURE_MAG_FILTER);
		glTextureParameteri(id, GL_TEXTURE_MIN_FILTER, DEFAULT_TEXTURE_MIN_FILTER);
		glNamedFramebufferTexture(m_ID, GL_COLOR_ATTACHMENT0 + index, id, 0);
		if (m_ColorAttachment.size() < index + 1) {
			unsigned int margin = index + 1 - m_ColorAttachment.size();
			for (unsigned int i = 0; i < margin; ++i)
				m_ColorAttachment.push_back(0);
		}
		// ���λ�����Ѿ���color attachment���򸲸ǲ�ɾ��
		if (m_ColorAttachment[index] != 0) {
			glDeleteTextures(1, &m_ColorAttachment[index]);
		}
		m_ColorAttachment[index] = id;
	}

	void FrameBuffer::addDepthTextureAttachment(unsigned int width, unsigned int height)
	{
		unsigned int id;
		glCreateTextures(GL_TEXTURE_2D, 1, &id);
		glTextureStorage2D(id, 1, GL_DEPTH_COMPONENT32, width, height);
		glTextureParameteri(id, GL_TEXTURE_MAG_FILTER, DEFAULT_TEXTURE_MAG_FILTER);
		glTextureParameteri(id, GL_TEXTURE_MIN_FILTER, DEFAULT_TEXTURE_MIN_FILTER);
		glNamedFramebufferTexture(m_ID, GL_DEPTH_ATTACHMENT, id, 0);
		// ����Ѿ���depth attachment���򸲸ǲ�ɾ��
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
		// ����Ѿ����ڣ��򸲸ǲ�ɾ��
		if (m_DepthRenderBufferAttachment != 0) {
			// TODO! Add to log
			glDeleteRenderbuffers(1, &m_DepthRenderBufferAttachment);
		}
		m_DepthRenderBufferAttachment = id;
	}

	void FrameBuffer::bind(unsigned int width, unsigned int height)
	{
		// ��֤ gl_texture_2d û�а�
		glBindTexture(GL_TEXTURE_2D, 0);
		glBindFramebuffer(GL_FRAMEBUFFER, m_ID);
		//// ���֡
		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glViewport(0, 0, width, height);
	}

	void FrameBuffer::unbind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glViewport(0, 0, Input::windowWidth, Input::windowHeight);
	}

	void FrameBuffer::setDrawBuffer(unsigned int index)
	{
		glDrawBuffer(GL_COLOR_ATTACHMENT0 + index);
	}

	void FrameBuffer::cleanUp()
	{
		glDeleteTextures(m_ColorAttachment.size(), m_ColorAttachment.data());
		m_ColorAttachment.clear();

		glDeleteTextures(1, &m_DepthTextureAttachment);
		m_DepthTextureAttachment = 0;

		glDeleteRenderbuffers(1, &m_DepthRenderBufferAttachment);
		m_DepthRenderBufferAttachment = 0;
	}

} }
