#include "post_process.h"

namespace sloth {
	void Constrast::process(unsigned int colorTexture)
	{
		// 因为 fbo 和纹理绑定有关，必须在激活纹理单元之前绑定
		bind();
		ConstrastShader::inst()->enable();
		ConstrastShader::inst()->contrast.loadFloat(0.4f);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, colorTexture);
		renderQuad();
		ConstrastShader::inst()->disable();
		unbind();
	}

	std::shared_ptr<ConstrastShader> ConstrastShader::inst()
	{
		static std::shared_ptr<ConstrastShader> inst = nullptr;
		if (inst.get() == nullptr)
			inst = std::shared_ptr<ConstrastShader>(new ConstrastShader());
		return inst;
	}

	void HorizontalBlur::process(unsigned int colorTexture, float targetWidth)
	{
		// 因为 fbo 和纹理绑定有关，必须在激活纹理单元之前绑定
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
		// 因为 fbo 和纹理绑定有关，必须在激活纹理单元之前绑定
		bind();
		VerticalBlurShader::inst()->enable();
		VerticalBlurShader::inst()->targetHeight.loadFloat(targetHeight);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, colorTexture);
		renderQuad();
		VerticalBlurShader::inst()->disable();
		unbind();
	}
	void LuminanceFilter::process(unsigned int colorTexture, float thresHold)
	{
		// 因为 fbo 和纹理绑定有关，必须在激活纹理单元之前绑定
		bind();
		LuminanceFilterShader::inst()->enable();
		LuminanceFilterShader::inst()->thresHold.loadFloat(thresHold);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, colorTexture);
		renderQuad();
		LuminanceFilterShader::inst()->disable();
		unbind();
	}
	void CombineFilter::process(unsigned int colorTexture, unsigned int highlightTexture, float scale)
	{
		// 因为 fbo 和纹理绑定有关，必须在激活纹理单元之前绑定
		bind();
		CombineFilterShader::inst()->enable();
		CombineFilterShader::inst()->scale.loadFloat(scale);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, colorTexture);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, highlightTexture);
		renderQuad();
		CombineFilterShader::inst()->disable();
		unbind();
	}

} 
