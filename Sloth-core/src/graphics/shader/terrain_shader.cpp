#include "terrain_shader.h"

namespace sloth { namespace graphics {

	TerrainShader* TerrainShader::m_Inst = nullptr;

	TerrainShader::TerrainShader()
		: Shader(TERRAIN_VERTEX_FILE, TERRAIN_FRAGMENT_FILE)
	{
		getAllUniformLocation();
	}

	TerrainShader::~TerrainShader()
	{
		delete m_Inst;
		delete[] m_LocLightPos;
		delete[] m_LocLightColor;
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

	void TerrainShader::loadViewMatrix(const Camera &camera)
	{
		glProgramUniformMatrix4fv(m_ID, m_LocView, 1, GL_FALSE, glm::value_ptr(camera.getViewMatrix()));
	}

	void TerrainShader::loadProjectionMatrix(const glm::mat4 & projection)
	{
		glProgramUniformMatrix4fv(m_ID, m_LocProjection, 1, GL_FALSE, glm::value_ptr(projection));
	}

	void TerrainShader::loadLights(const std::vector<Light>& lights)
	{
		for (size_t i = 0; i < GLSL_MAX_LIGHTS; ++i) {
			if (i < lights.size()) {
				glProgramUniform3f(m_ID, m_LocLightPos[i], lights[i].position[0], lights[i].position[1], lights[i].position[2]);
				glProgramUniform3f(m_ID, m_LocLightColor[i], lights[i].color[0], lights[i].color[1], lights[i].color[2]);
			}
			else {
				glProgramUniform3f(m_ID, m_LocLightPos[i], 0.0f, 0.0f, 0.0f);
				glProgramUniform3f(m_ID, m_LocLightColor[i], 0.0f, 0.0f, 0.0f);
			}
		}
	}

	void TerrainShader::loadShineVariable(const float shininess, const float reflectivity)
	{
		glProgramUniform1f(m_ID, m_LocShininess, shininess);
		glProgramUniform1f(m_ID, m_LocReflectivity, reflectivity);
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

		for (int i = 0; i < GLSL_MAX_LIGHTS; ++i) {
			char c = '0' + i;
			m_LocLightPos[i] = glGetUniformLocation(m_ID, (std::string("lightPosition[") + c + "]").c_str());
			m_LocLightColor[i] = glGetUniformLocation(m_ID, (std::string("lightColor[") + c + "]").c_str());
		}

	}
} }
