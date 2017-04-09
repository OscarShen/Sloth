#include "post_process.h"

namespace sloth { namespace graphics {
	void Constrast::process(unsigned int colorTexture)
	{
		// ��Ϊ fbo ��������йأ������ڼ�������Ԫ֮ǰ��
		bind();
		ConstrastShader::inst()->enable();
		ConstrastShader::inst()->contrast.loadFloat(0.4f);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, colorTexture);
		renderQuad();
		ConstrastShader::inst()->disable();
		unbind();
	}

	std::shared_ptr<ConstrastShader> graphics::ConstrastShader::inst()
	{
		static std::shared_ptr<ConstrastShader> inst = nullptr;
		if (inst.get() == nullptr)
			inst = std::shared_ptr<ConstrastShader>(new ConstrastShader());
		return inst;
	}

	void HorizontalBlur::process(unsigned int colorTexture, float targetWidth)
	{
		// ��Ϊ fbo ��������йأ������ڼ�������Ԫ֮ǰ��
		bind();
		HorizontalBlurShader::inst()->enable();
		HorizontalBlurShader::inst()->targetWidth.loadFloat(targetWidth);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, colorTexture);
		renderQuad();
		HorizontalBlurShader::inst()->disable();
		unbind();
	}
	void VerticalBlur::process(unsigned int colorTexture, float targetHeight)
	{
		// ��Ϊ fbo ��������йأ������ڼ�������Ԫ֮ǰ��
		bind();
		VerticalBlurShader::inst()->enable();
		VerticalBlurShader::inst()->targetHeight.loadFloat(targetHeight);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, colorTexture);
		renderQuad();
		HorizontalBlurShader::inst()->disable();
		unbind();
	}
} }
