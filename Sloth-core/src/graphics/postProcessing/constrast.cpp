#include "constrast.h"

namespace sloth { namespace graphics {
	void Constrast::process(unsigned int colorTexture)
	{
		// 因为 fbo 和纹理绑定有关，必须在这儿进行绑定
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
} }
