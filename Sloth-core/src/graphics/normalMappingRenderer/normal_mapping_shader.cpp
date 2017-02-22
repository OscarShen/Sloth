#include "normal_mapping_shader.h"

namespace sloth { namespace graphics {

	NormalMappingShader* NormalMappingShader::m_Inst(nullptr);

	NormalMappingShader::NormalMappingShader()
		:Shader(NORMAL_MAPPING_VERTEX_FILE, NORMAL_MAPPING_FRAGMENT_FILE)
	{
		getAllUniformLocation();
	}

	NormalMappingShader::~NormalMappingShader()
	{
		delete m_Inst;
		delete[] m_LocLightPos;
		delete[] m_LocLightColor;
	}

	NormalMappingShader * NormalMappingShader::inst()
	{
		if (!m_Inst)
			m_Inst = new NormalMappingShader();
		return m_Inst;
	}

	void NormalMappingShader::loadModelMatrix(const glm::mat4 & model)
	{
		glProgramUniformMatrix4fv(m_ID, m_LocModel, 1, GL_FALSE, glm::value_ptr(model));
	}

	void NormalMappingShader::loadViewMatrix(const RawCamera &camera)
	{
		glProgramUniformMatrix4fv(m_ID, m_LocView, 1, GL_FALSE, glm::value_ptr(camera.getViewMatrix()));
	}

	void NormalMappingShader::loadProjectionMatrix(const glm::mat4 & projection)
	{
		glProgramUniformMatrix4fv(m_ID, m_LocProjection, 1, GL_FALSE, glm::value_ptr(projection));
	}

	void NormalMappingShader::loadLight(const Light & light)
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

	void NormalMappingShader::loadLights(const std::vector<Light>& lights)
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

	void NormalMappingShader::loadShineVariable(const float shininess, const float reflectivity)
	{
		glProgramUniform1f(m_ID, m_LocShininess, shininess);
		glProgramUniform1f(m_ID, m_LocReflectivity, reflectivity);
	}

	void NormalMappingShader::loadSkyColor(const float r, const float g, const float b)
	{
		glProgramUniform3f(m_ID, m_LocSkyColor, r, g, b);
	}

	void NormalMappingShader::loadNumberOfRows(int numberOfRaws)
	{
		glProgramUniform1f(m_ID, m_LocNumberOfRows, (float)numberOfRaws);
	}

	void NormalMappingShader::loadOffset(float x, float y)
	{
		glProgramUniform2f(m_ID, m_LocOffset, x, y);
	}

	void NormalMappingShader::loadClipPlane(const glm::vec4 & clipPlane)
	{
		glProgramUniform4f(m_ID, m_LocClipPlane, clipPlane.x, clipPlane.y, clipPlane.z, clipPlane.w);
	}

	void NormalMappingShader::getAllUniformLocation()
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

		m_LocSkyColor = glGetUniformLocation(m_ID, "skyColor");
		m_LocNumberOfRows = glGetUniformLocation(m_ID, "numberOfRows");
		m_LocOffset = glGetUniformLocation(m_ID, "offset");
		m_LocClipPlane = glGetUniformLocation(m_ID, "clipPlane");
		m_LocNormalMap = glGetUniformLocation(m_ID, "normalMap");
		m_LocDiffuseMap = glGetUniformLocation(m_ID, "diffuseMap");
	}
	void NormalMappingShader::connectTextureUnit()
	{
		glProgramUniform1i(m_ID, m_LocDiffuseMap, 0);
		glProgramUniform1i(m_ID, m_LocNormalMap, 1);
	}
} }
