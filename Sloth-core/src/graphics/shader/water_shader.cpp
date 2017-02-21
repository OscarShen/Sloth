#include "water_shader.h"

namespace sloth { namespace graphics {

	WaterShader *WaterShader::m_Inst(nullptr);

	WaterShader * WaterShader::inst()
	{
		if (m_Inst == nullptr)
			m_Inst = new WaterShader();
		return m_Inst;
	}

	WaterShader::~WaterShader()
	{
		delete m_Inst;
	}

	void WaterShader::connectTextureUnit()
	{
		glProgramUniform1i(m_ID, m_LocReflectionTexture, 0);
		glProgramUniform1i(m_ID, m_LocRefractionTexture, 1);
		glProgramUniform1i(m_ID, m_LocDudvMap, 2);
		glProgramUniform1i(m_ID, m_LocNormalMap, 3);
		glProgramUniform1i(m_ID, m_LocDepthMap, 4);
	}

	WaterShader::WaterShader()
		:Shader(WATER_VERTEX_FILE, WATER_FRAGMENT_FILE)
	{
		getAllUniformLocation();
	}

	void WaterShader::getAllUniformLocation()
	{
		m_LocModel = glGetUniformLocation(m_ID, "model");
		m_LocView = glGetUniformLocation(m_ID, "view");
		m_LocProjection = glGetUniformLocation(m_ID, "projection");
		m_LocReflectionTexture = glGetUniformLocation(m_ID, "reflectionTexture");
		m_LocRefractionTexture = glGetUniformLocation(m_ID, "refractionTexture");
		m_LocDudvMap = glGetUniformLocation(m_ID, "dudvMap");
		m_LocMoveFactor = glGetUniformLocation(m_ID, "moveFactor");
		m_LocCameraPosition = glGetUniformLocation(m_ID, "cameraPosition");
		m_LocNormalMap = glGetUniformLocation(m_ID, "normalMap");
		m_LocLightColor = glGetUniformLocation(m_ID, "lightColor");
		m_LocLightPosition = glGetUniformLocation(m_ID, "lightPosition");
		m_LocDepthMap = glGetUniformLocation(m_ID, "depthMap");
	}

	void WaterShader::loadModelMatrix(const glm::mat4 & model)
	{
		glProgramUniformMatrix4fv(m_ID, m_LocModel, 1, GL_FALSE, glm::value_ptr(model));
	}

	void WaterShader::loadViewMatrix(const RawCamera &camera)
	{
		glProgramUniformMatrix4fv(m_ID, m_LocView, 1, GL_FALSE, glm::value_ptr(camera.getViewMatrix()));
	}

	void WaterShader::loadProjectionMatrix(const glm::mat4 & projection)
	{
		glProgramUniformMatrix4fv(m_ID, m_LocProjection, 1, GL_FALSE, glm::value_ptr(projection));
	}

	void WaterShader::loadMoveFactor(float factor)
	{
		glProgramUniform1f(m_ID, m_LocMoveFactor, factor);
	}

	void WaterShader::loadCameraPosition(const RawCamera & camera)
	{
		auto position = camera.getPosition();
		glProgramUniform3fv(m_ID,m_LocCameraPosition,1,&position.x);
	}

	void WaterShader::loadLight(const Light & light)
	{
		glProgramUniform3fv(m_ID, m_LocLightPosition, 1, &light.position.x);
		glProgramUniform3fv(m_ID, m_LocLightColor, 1, &light.color.x);
	}

} }
