#include "gui_shader.h"

namespace sloth { namespace graphics {
	std::shared_ptr<GuiShader> GuiShader::m_Inst(nullptr);
	std::shared_ptr<GuiShader> GuiShader::inst()
	{
		if (m_Inst == nullptr)
			m_Inst = std::shared_ptr<GuiShader>(new GuiShader());
		return m_Inst;
	}

	void GuiShader::loadTransformation(glm::mat4 & matrix)
	{
		loadMatrix4(m_LocTransformationMatrix, matrix);
	}

	GuiShader::GuiShader()
		:Shader(GUI_VERTEX_FILE, GUI_FRAGMENT_FILE)
	{
		getAllUniformLocation();
	}

	void GuiShader::getAllUniformLocation()
	{
		m_LocTransformationMatrix = glGetUniformLocation(m_ID, "transformationMatrix");
	}

} }
