#include "water_renderer.h"

namespace sloth { namespace graphics {
	WaterRenderer::WaterRenderer(Loader & loader, const glm::mat4 & projection, WaterFrameBuffer &waterfbo)
		:m_Wfbo(waterfbo)
	{
		WaterShader::inst()->loadProjectionMatrix(projection);
		WaterShader::inst()->connectTextureUnit();
		setVAO(loader);
	}

	void WaterRenderer::render(std::vector<WaterTile>& water, RawCamera & camera)
	{
		auto shader = WaterShader::inst();
		shader->enable();
		shader->loadViewMatrix(camera);
		glBindVertexArray(m_Quad.getVaoID());
		glEnableVertexAttribArray(0);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_Wfbo.getReflectionTexture());
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, m_Wfbo.getRefractionTexture());

		for (auto it = water.begin(); it != water.end(); ++it) {
			glm::mat4 model = util::Maths::createModelMatrix(glm::vec3(it->getCenterX(), it->getHeight(), it->getCenterZ()), 0.0f, 0.0f, 0.0f, WATER_TILE_SIZE);
			shader->loadModelMatrix(model);
			glDrawArrays(GL_TRIANGLES, 0, m_Quad.getVertexCount());
		}
		glDisableVertexAttribArray(0);
		glBindVertexArray(0);
		shader->disable();
	}

	void WaterRenderer::setVAO(Loader & loader)
	{
		std::vector<float> vertices = { -1, -1, -1, 1, 1, -1, 1, -1, -1, 1, 1, 1 };
		// 暂时设定水面高度为0.0f
		m_Quad = loader.loadToVAO(vertices, 2);
	}

} }
