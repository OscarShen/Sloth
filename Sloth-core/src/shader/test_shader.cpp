#include "test_shader.h"
namespace sloth { 

	TestShader * TestShader::m_Inst(nullptr);

	TestShader * TestShader::inst()
	{
		if (m_Inst == nullptr)
			m_Inst = new TestShader();
		return m_Inst;
	}

	void TestShader::loadModel(const glm::mat4 & model)
	{
		glProgramUniformMatrix4fv(m_ID, m_LocModel, 1, GL_FALSE, glm::value_ptr(model));
	}

	void TestShader::loadView(const glm::mat4 & view)
	{
		glProgramUniformMatrix4fv(m_ID, m_LocView, 1, GL_FALSE, glm::value_ptr(view));
	}

	void TestShader::loadProjection(const glm::mat4 & projection)
	{
		glProgramUniformMatrix4fv(m_ID, m_LocProjection, 1, GL_FALSE, glm::value_ptr(projection));
	}

	TestShader::TestShader()
		:Shader(TEST_VERTEX_FILE,TEST_FRAGMENT_FILE)
	{
		getAllUniformLocation();
	}

	void TestShader::getAllUniformLocation()
	{
		m_LocModel = glGetUniformLocation(m_ID, "model");
		m_LocView = glGetUniformLocation(m_ID, "view");
		m_LocProjection = glGetUniformLocation(m_ID, "projection");
	}

} 
