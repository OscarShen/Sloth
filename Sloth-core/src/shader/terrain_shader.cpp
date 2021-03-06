#include "terrain_shader.h"

namespace sloth {

	TerrainShader* TerrainShader::m_Inst = nullptr;

	TerrainShader::TerrainShader()
		: Shader(TERRAIN_VERTEX_FILE, TERRAIN_FRAGMENT_FILE)
	{
		getAllUniformLocation();
	}

	TerrainShader::~TerrainShader()
	{
		delete[] m_LocLightPos;
		delete[] m_LocLightColor;
		delete[] m_LocAttenuation;
		m_Inst = nullptr;
	}

	TerrainShader * TerrainShader::inst()
	{
		if (!m_Inst)
			m_Inst = new TerrainShader();
		return m_Inst;
	}

	void TerrainShader::loadModelMatrix(const glm::mat4 & model)
	{
		glProgramUniformMatrix4fv(m_ID, m_LocModel, 1, GL_FALSE, glm::value_ptr(model));
	}

	void TerrainShader::loadViewMatrix(const RawCamera &camera)
	{
		glProgramUniformMatrix4fv(m_ID, m_LocView, 1, GL_FALSE, glm::value_ptr(camera.getViewMatrix()));
	}

	void TerrainShader::loadProjectionMatrix(const glm::mat4 & projection)
	{
		glProgramUniformMatrix4fv(m_ID, m_LocProjection, 1, GL_FALSE, glm::value_ptr(projection));
	}

	void TerrainShader::loadLight(const Light & light)
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

	void TerrainShader::loadLights(const std::vector<Light>& lights)
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

	void TerrainShader::loadShineVariable(const float shininess, const float reflectivity)
	{
		glProgramUniform1f(m_ID, m_LocShininess, shininess);
		glProgramUniform1f(m_ID, m_LocReflectivity, reflectivity);
	}

	void TerrainShader::loadSkyColor(const float r, const float g, const float b)
	{
		glProgramUniform3f(m_ID, m_LocSkyColor, r, g, b);
	}

	void TerrainShader::connectTextureUnits()
	{
		glProgramUniform1i(m_ID, m_LocBackgroundTexture, 0);
		glProgramUniform1i(m_ID, m_LocRTexture, 1);
		glProgramUniform1i(m_ID, m_LocGTexture, 2);
		glProgramUniform1i(m_ID, m_LocBTexture, 3);
		glProgramUniform1i(m_ID, m_LocBlendMapTexture, 4);
		glProgramUniform1i(m_ID, m_LocShadowMap, 5);
	}

	void TerrainShader::loadClipPlane(const glm::vec4 & clipPlane)
	{
		glProgramUniform4f(m_ID, m_LocClipPlane, clipPlane.x, clipPlane.y, clipPlane.z, clipPlane.w);
	}

	void TerrainShader::loadLightSpace(const glm::mat4 & lightSpace)
	{
		glProgramUniformMatrix4fv(m_ID, m_LocLightSpace, 1, GL_FALSE, glm::value_ptr(lightSpace));
	}

	void TerrainShader::getAllUniformLocation()
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
		m_LocBackgroundTexture = glGetUniformLocation(m_ID, "backgroundTexture");
		m_LocRTexture = glGetUniformLocation(m_ID, "rTexture");
		m_LocGTexture = glGetUniformLocation(m_ID, "gTexture");
		m_LocBTexture = glGetUniformLocation(m_ID, "bTexture");
		m_LocBlendMapTexture = glGetUniformLocation(m_ID, "blendMap");
		m_LocClipPlane = glGetUniformLocation(m_ID, "clipPlane");
		m_LocLightSpace = glGetUniformLocation(m_ID, "lightSpace");
		m_LocShadowMap = glGetUniformLocation(m_ID, "shadowMap");
	}


} 
