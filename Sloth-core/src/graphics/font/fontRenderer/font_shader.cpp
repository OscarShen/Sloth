#include "font_shader.h"

namespace sloth { namespace graphics {
	FontShader * FontShader::m_Inst(nullptr);

	FontShader::FontShader()
		: Shader(FONT_SHADER_VERTEX_FILE, FONT_SHADER_FRAGMENT_FILE)
	{ 
		getAllUniformLocation();
	}

	FontShader * FontShader::inst()
	{
		if (m_Inst == nullptr)
			m_Inst = new FontShader();
		return m_Inst;
	}

	void sloth::graphics::FontShader::loadColor(const glm::vec3 & color)
	{
		glProgramUniform3f(m_ID, m_LocColor, color.x, color.y, color.z);
	}

	void sloth::graphics::FontShader::loadModel(const glm::vec2 &model)
	{
		glProgramUniform2f(m_ID, m_LocModel, model.x, model.y);
	}

	void sloth::graphics::FontShader::getAllUniformLocation()
	{
		m_LocColor = glGetUniformLocation(m_ID, "color");
		m_LocModel = glGetUniformLocation(m_ID, "model");
	}

} }
