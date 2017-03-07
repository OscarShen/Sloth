#include "particle_renderer.h"

namespace sloth { namespace graphics {

	std::vector<float> ParticleRenderer::VERTICES = { -0.5f, 0.5f, -0.5f, -0.5f, 0.5f, 0.5f, 0.5f, -0.5f };

	ParticleRenderer::ParticleRenderer(Loader & loader, const glm::mat4 & projection)
	{
		m_Quad = loader.loadToVAO(VERTICES, 2);
		ParticleShader::inst()->projection.loadMatrix4(projection);
	}

	void ParticleRenderer::render(const std::unordered_map<ParticleTexture ,std::shared_ptr<std::list<std::shared_ptr<Particle>>>> & particles, RawCamera & camera)
	{
		prepare();
		for (auto &pair : particles) {
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, pair.first.getTextureID());
			if (pair.first.isAdditive())
				glBlendFunc(GL_SRC_ALPHA, GL_ONE);
			else
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			for (auto &particle : *(pair.second)) {
				updateModelView(particle->getPosition(), particle->getRotation(), particle->getScale(), camera.getViewMatrix());
				ParticleShader::inst()->loadTextureCoordInfo(particle->getTexOffsetNow(), particle->getTexOffsetNext(),
					static_cast<float>(pair.first.getNumberOfRows()), particle->getBlendFactor());
				glDrawArrays(GL_TRIANGLE_STRIP, 0, m_Quad.getVertexCount());
			}
		}
		unbind();
	}

	void ParticleRenderer::prepare()
	{
		ParticleShader::inst()->enable();
		glBindVertexArray(m_Quad.getVaoID());
		glEnableVertexAttribArray(0);
		glEnable(GL_BLEND);
		//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		glDepthMask(false);
		glDisable(GL_CULL_FACE);
	}

	void ParticleRenderer::updateModelView(const glm::vec3 & position, float rotation, float scale, const glm::mat4 & view)
	{
		glm::mat4 modelView;
		// view 矩阵是正交矩阵，且粒子不需要旋转分量
		modelView = glm::translate(position);
		modelView = glm::rotate(modelView, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
		modelView[0][0] = view[0][0];
		modelView[0][1] = view[1][0];
		modelView[0][2] = view[2][0];
		modelView[1][0] = view[0][1];
		modelView[1][1] = view[1][1];
		modelView[1][2] = view[2][1];
		modelView[2][0] = view[0][2];
		modelView[2][1] = view[1][2];
		modelView[2][2] = view[2][2];
		modelView =  view * modelView;
		modelView = glm::scale(modelView, glm::vec3(scale));
		ParticleShader::inst()->modelView.loadMatrix4(modelView);
	}

	void ParticleRenderer::unbind()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
		glEnable(GL_CULL_FACE);
		glDepthMask(true);
		glDisable(GL_BLEND);
		glDisableVertexAttribArray(0);
		glBindVertexArray(0);
		ParticleShader::inst()->disable();
	}

} }
