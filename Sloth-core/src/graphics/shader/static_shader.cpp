#include "static_shader.h"

namespace sloth { namespace graphics {

	StaticShader* StaticShader::m_Inst(nullptr);

	StaticShader::StaticShader()
		:Shader(STATIC_VERTEX_FILE, STATIC_FRAGMENT_FILE)
	{
		getAllUniformLocation();
	}

	StaticShader::~StaticShader()
	{
		delete m_Inst;
		delete[] m_LocLightPos;
		delete[] m_LocLightColor;
	}

	StaticShader * StaticShader::inst()
	{
		if (!m_Inst)
			m_Inst = new StaticShader();
		return m_Inst;
	}

	void StaticShader::loadModelMatrix(const glm::mat4 & model)
	{
		glProgramUniformMatrix4fv(m_ID, m_LocModel, 1, GL_FALSE, glm::value_ptr(model));
	}

	void StaticShader::loadViewMatrix(const RawCamera &camera)
	{
		glProgramUniformMatrix4fv(m_ID, m_LocView, 1, GL_FALSE, glm::value_ptr(camera.getViewMatrix()));
	}

	void StaticShader::loadProjectionMatrix(const glm::mat4 & projection)
	{
		glProgramUniformMatrix4fv(m_ID, m_LocProjection, 1, GL_FALSE, glm::value_ptr(projection));
	}

	void StaticShader::loadLight(const Light & light)
	{
		glProgramUniform3f(m_ID, m_LocLightPos[0], light.position[0], light.position[1], light.position[2]);
		glProgramUniform3f(m_ID, m_LocLightColor[0], light.color[0], light.color[1], light.color[2]);
		glProgramUniform3f(m_ID, m_LocAttenuation[0], light.attenuation[0], light.attenuation[1], light.attenuation[2]);
		for (int i = 1; i < GLSL_MAX_LIGHTS; ++i) {
			glProgramUniform3f(m_ID, m_LocLightPos[i], 0.0f, 0.0f, 0.0f);
			glProgramUniform3f(m_ID, m_LocLightColor[i], 0.0f, 0.0f, 0.0f);
			glProgramUniform3f(m_ID, m_LocAttenuation[i], 1.0f, 0.0f, 0.0f);
		}
	}

	void StaticShader::loadLights(const std::vector<Light>& lights)
	{
		for (size_t i = 0; i < GLSL_MAX_LIGHTS; ++i) {
			if (i < lights.size()) {
				glProgramUniform3f(m_ID, m_LocLightPos[i], lights[i].position[0], lights[i].position[1], lights[i].position[2]);
				glProgramUniform3f(m_ID, m_LocLightColor[i], lights[i].color[0], lights[i].color[1], lights[i].color[2]);
				glProgramUniform3f(m_ID, m_LocAttenuation[i], lights[i].attenuation[0], lights[i].attenuation[1], lights[i].attenuation[2]);
			}
			else {
				glProgramUniform3f(m_ID, m_LocLightPos[i], 0.0f, 0.0f, 0.0f);
				glProgramUniform3f(m_ID, m_LocLightColor[i], 0.0f, 0.0f, 0.0f);
				glProgramUniform3f(m_ID, m_LocAttenuation[i], 1.0f, 0.0f, 0.0f);
			}
		}
	}

	void StaticShader::loadShineVariable(const float shininess, const float reflectivity)
	{
		glProgramUniform1f(m_ID, m_LocShininess, shininess);
		glProgramUniform1f(m_ID, m_LocReflectivity, reflectivity);
	}

	void StaticShader::loadUseFakeLighting(const bool useFake)
	{
		if (useFake)
			glProgramUniform1f(m_ID, m_LocUseFakeLighting, 1.0f);
		else
			glProgramUniform1f(m_ID, m_LocUseFakeLighting, 0.0f);
	}

	void StaticShader::loadSkyColor(const float r, const float g, const float b)
	{
		glProgramUniform3f(m_ID, m_LocSkyColor, r, g, b);
	}

	void StaticShader::loadNumberOfRows(int numberOfRaws)
	{
		glProgramUniform1f(m_ID, m_LocNumberOfRows, (float)numberOfRaws);
	}

	void StaticShader::loadOffset(float x, float y)
	{
		glProgramUniform2f(m_ID, m_LocOffset, x, y);
	}

	void StaticShader::getAllUniformLocation()
	{
		m_LocModel = glGetUniformLocation(m_ID, "model");
		m_LocView = glGetUniformLocation(m_ID, "view");
		m_LocProjection = glGetUniformLocation(m_ID, "projection");
		m_LocShininess = glGetUniformLocation(m_ID, "shininess");
		m_LocReflectivity = glGetUniformLocation(m_ID, "reflectivity");
		m_LocLightPos = new int[GLSL_MAX_LIGHTS];
		m_LocLightColor = new int[GLSL_MAX_LIGHTS];
		m_LocAttenuation = new int[GLSL_MAX_LIGHTS];

		for (int i = 0; i < GLSL_MAX_LIGHTS; ++i) {
			char c = '0' + i;
			m_LocLightPos[i] = glGetUniformLocation(m_ID, (std::string("lightPosition[") + c + "]").c_str());
			m_LocLightColor[i] = glGetUniformLocation(m_ID, (std::string("lightColor[") + c + "]").c_str());
			m_LocAttenuation[i] = glGetUniformLocation(m_ID, (std::string("attenuation[") + c + "]").c_str());
		}

		m_LocUseFakeLighting = glGetUniformLocation(m_ID, "useFakeLignting");
		m_LocSkyColor = glGetUniformLocation(m_ID, "skyColor");
		m_LocNumberOfRows = glGetUniformLocation(m_ID, "numberOfRows");
		m_LocOffset = glGetUniformLocation(m_ID, "offset");
	}
} }
