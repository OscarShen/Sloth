#include "font_shader.h"

namespace sloth { namespace graphics {
	std::shared_ptr<FontShader> FontShader::m_Inst(nullptr);

	FontShader::FontShader()
		: Shader(FONT_SHADER_VERTEX_FILE, FONT_SHADER_FRAGMENT_FILE)
	{ 
		getAllUniformLocation();
	}

	std::shared_ptr<FontShader> FontShader::inst()
	{
		if (m_Inst == nullptr)
			m_Inst = FontShader_s(new FontShader());
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

	void FontShader::loadFontWidth(float fontWidth)
	{
		glProgramUniform1f(m_ID, m_LocFontWidth, fontWidth);
	}

	void FontShader::loadFontEdge(float fontEdge)
	{
		glProgramUniform1f(m_ID, m_LocFontEdge, fontEdge);
	}

	void FontShader::loadBorderWidth(float borderWidth)
	{
		glProgramUniform1f(m_ID, m_LocBorderWidth, borderWidth);
	}

	void FontShader::loadBorderEdge(float borderEdge)
	{
		glProgramUniform1f(m_ID, m_LocBorderEdge, borderEdge);
	}

	void FontShader::loadOffset(const glm::vec2 & offset)
	{
		glProgramUniform2f(m_ID, m_LocOffset, offset.x, offset.y);
	}

	void FontShader::loadOutlineColor(const glm::vec3 & outlineColor)
	{
		glProgramUniform3f(m_ID, m_LocOutlineColor, outlineColor.x, outlineColor.y, outlineColor.z);
	}

	void sloth::graphics::FontShader::getAllUniformLocation()
	{
		m_LocColor = glGetUniformLocation(m_ID, "color");
		m_LocModel = glGetUniformLocation(m_ID, "model");
		m_LocFontWidth = glGetUniformLocation(m_ID, "fontWidth");
		m_LocFontEdge = glGetUniformLocation(m_ID, "fontEdge");
		m_LocBorderWidth = glGetUniformLocation(m_ID, "borderWidth");
		m_LocBorderEdge = glGetUniformLocation(m_ID, "borderEdge");
		m_LocOffset = glGetUniformLocation(m_ID, "offset");
		m_LocOutlineColor = glGetUniformLocation(m_ID, "outlineColor");
	}

} }
