#include "gaussian_blur.h"

namespace sloth { namespace graphics {
	void HorizontalBlur::doPostProcessing(unsigned int colorTexture)
	{
		start();
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, colorTexture);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, quad.getVertexCount());
		end();
	}
	void HorizontalBlur::start()
	{
		auto shader = HorizontalBlurShader::inst();
		shader->enable();
		// TODO : 不要硬编码
		shader->targetWidth.loadFloat(SCREEN_WIDTH);
		glBindVertexArray(quad.getVaoID());
		glEnableVertexAttribArray(0);
		glDisable(GL_DEPTH_TEST);
	}

	void HorizontalBlur::end()
	{
		glEnable(GL_DEPTH_TEST);
		glDisableVertexAttribArray(0);
		glBindVertexArray(0);
		HorizontalBlurShader::inst()->disable();
	}

	std::shared_ptr<HorizontalBlurShader> graphics::HorizontalBlurShader::inst()
	{
		static std::shared_ptr<HorizontalBlurShader> instance(new HorizontalBlurShader());
		return instance;
	}

	void VerticalBlur::doPostProcessing(unsigned int colorTexture)
	{
		start();
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, colorTexture);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, quad.getVertexCount());
		end();
	}
	void VerticalBlur::start()
	{
		auto shader = VerticalBlurShader::inst();
		shader->enable();
		// TODO : 不要硬编码
		shader->targetHeight.loadFloat(SCREEN_WIDTH);
		glBindVertexArray(quad.getVaoID());
		glEnableVertexAttribArray(0);
		glDisable(GL_DEPTH_TEST);
	}

	void VerticalBlur::end()
	{
		glEnable(GL_DEPTH_TEST);
		glDisableVertexAttribArray(0);
		glBindVertexArray(0);
		VerticalBlurShader::inst()->disable();
	}

	std::shared_ptr<VerticalBlurShader> graphics::VerticalBlurShader::inst()
	{
		static std::shared_ptr<VerticalBlurShader> instance(new VerticalBlurShader());
		return instance;
	}
} }
