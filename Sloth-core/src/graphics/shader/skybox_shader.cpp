#include "skybox_shader.h"

namespace sloth { namespace graphics {
	SkyboxShader * SkyboxShader::m_Inst(nullptr);

	SkyboxShader * sloth::graphics::SkyboxShader::inst()
	{
		if (m_Inst == nullptr)
			m_Inst = new SkyboxShader();
		return m_Inst;
	}

	void SkyboxShader::loadFogColor(float r, float g, float b)
	{
		glProgramUniform3f(m_ID, m_LocFogColor, r, g, b);
	}

	SkyboxShader::SkyboxShader()
		:Shader(SKYBOX_VERTEX_FILE, SKYBOX_FRAGMENT_FILE)
	{
		getAllUniformLocation();
	}

	void SkyboxShader::loadViewMatrix(const RawCamera &camera)
	{
		// 天空盒需要随着相机移动，去除平移分量
		glm::mat4 view = camera.getViewMatrix();
		view[3][0] = 0.0f;
		view[3][1] = 0.0f;
		view[3][2] = 0.0f;
		glProgramUniformMatrix4fv(m_ID, m_LocView, 1, GL_FALSE, glm::value_ptr(view));
	}

	void SkyboxShader::loadProjectionMatrix(const glm::mat4 & projection)
	{
		glProgramUniformMatrix4fv(m_ID, m_LocProjection, 1, GL_FALSE, glm::value_ptr(projection));
	}

	void SkyboxShader::getAllUniformLocation()
	{
		m_LocProjection = glGetUniformLocation(m_ID, "projection");
		m_LocView = glGetUniformLocation(m_ID, "view");
		m_LocFogColor = glGetUniformLocation(m_ID, "fogColor");
	}

} }
