#include "constrast.h"

namespace sloth { namespace graphics {
	void Constrast::doPostProcessing(unsigned int colorTexture)
	{
		start();
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, colorTexture);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, quad.getVertexCount());
		end();
	}

	void Constrast::start()
	{
		ConstrastShader::inst()->enable();
		// TODO : 参数设置不要硬编码~！
		ConstrastShader::inst()->contrast.loadFloat(0.2f);
		glBindVertexArray(quad.getVaoID());
		glEnableVertexAttribArray(0);
		glDisable(GL_DEPTH_TEST);
	}

	void Constrast::end()
	{
		glEnable(GL_DEPTH_TEST);
		glDisableVertexAttribArray(0);
		glBindVertexArray(0);
		ConstrastShader::inst()->disable();
	}

	std::shared_ptr<ConstrastShader> graphics::ConstrastShader::inst()
	{
		static std::shared_ptr<ConstrastShader> inst = nullptr;
		if (inst.get() == nullptr)
			inst = std::shared_ptr<ConstrastShader>(new ConstrastShader());
		return inst;
	}



}
}
