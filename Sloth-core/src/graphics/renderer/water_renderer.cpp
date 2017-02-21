#include "water_renderer.h"

namespace sloth { namespace graphics {
	WaterRenderer::WaterRenderer(Loader & loader, const glm::mat4 & projection, WaterFrameBuffer &waterfbo)
		:m_Wfbo(waterfbo)
	{
		WaterShader::inst()->loadProjectionMatrix(projection);
		WaterShader::inst()->connectTextureUnit();
		setVAO(loader);
		m_DudvMap = loader.loadTexture(DUDV_MAP_PATH);
		m_NormalMap = loader.loadTexture(NORMAL_MAP_PATH);
	}

	void WaterRenderer::render(std::vector<WaterTile>& water, RawCamera & camera, const Light &light)
	{
		prepareRender(camera, light);
		for (auto it = water.begin(); it != water.end(); ++it) {
			glm::mat4 model = util::Maths::createModelMatrix(glm::vec3(it->getCenterX(), it->getHeight(), it->getCenterZ()), 0.0f, 0.0f, 0.0f, WATER_TILE_SIZE);
			WaterShader::inst()->loadModelMatrix(model);
			glDrawArrays(GL_TRIANGLES, 0, m_Quad.getVertexCount());
		}
		unbind();
	}

	void WaterRenderer::setVAO(Loader & loader)
	{
		std::vector<float> vertices = { -1, -1, -1, 1, 1, -1, 1, -1, -1, 1, 1, 1 };
		// 暂时设定水面高度为0.0f
		m_Quad = loader.loadToVAO(vertices, 2);
	}

	void WaterRenderer::prepareRender(const RawCamera &camera, const Light &light)
	{
		WaterShader::inst()->enable();
		WaterShader::inst()->loadViewMatrix(camera);
		WaterShader::inst()->loadCameraPosition(camera);
		WaterShader::inst()->loadLight(light);

		m_MoveFactor += WATER_WAVE_SPEED * static_cast<float>(util::Timer::deltaFrameTime);
		m_MoveFactor = std::fmod(m_MoveFactor, 1.0f);
		WaterShader::inst()->loadMoveFactor(m_MoveFactor);

		glBindVertexArray(m_Quad.getVaoID());
		glEnableVertexAttribArray(0);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_Wfbo.getReflectionTexture());
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, m_Wfbo.getRefractionTexture());
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, m_DudvMap);
		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, m_NormalMap);
		glActiveTexture(GL_TEXTURE4);
		glBindTexture(GL_TEXTURE_2D, m_Wfbo.getRefractionDepthTexture());

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void WaterRenderer::unbind()
	{
		glDisable(GL_BLEND);
		glDisableVertexAttribArray(0);
		glBindVertexArray(0);
		WaterShader::inst()->disable();
	}

} }
