#include "particle_renderer.h"

namespace sloth { namespace graphics {

	std::vector<float> ParticleRenderer::VERTICES = { -0.5f, 0.5f, -0.5f, -0.5f, 0.5f, 0.5f, 0.5f, -0.5f };

	ParticleRenderer::ParticleRenderer(Loader & loader, const glm::mat4 & projection)
		:m_Loader(loader)
	{
		m_Quad = loader.loadToVAO(VERTICES, 2);
		glBindVertexArray(m_Quad.getVaoID());
		m_Vbo = loader.createEmptyVbo(INSTANCE_DATA_LENGTH * MAX_INSTANCES);
		loader.addIntancedAttribute(m_Quad.getVaoID(), m_Vbo, 1, 4, INSTANCE_DATA_LENGTH, 0);
		loader.addIntancedAttribute(m_Quad.getVaoID(), m_Vbo, 2, 4, INSTANCE_DATA_LENGTH, 4);
		loader.addIntancedAttribute(m_Quad.getVaoID(), m_Vbo, 3, 4, INSTANCE_DATA_LENGTH, 8);
		loader.addIntancedAttribute(m_Quad.getVaoID(), m_Vbo, 4, 4, INSTANCE_DATA_LENGTH, 12);
		loader.addIntancedAttribute(m_Quad.getVaoID(), m_Vbo, 5, 4, INSTANCE_DATA_LENGTH, 16);
		loader.addIntancedAttribute(m_Quad.getVaoID(), m_Vbo, 6, 1, INSTANCE_DATA_LENGTH, 20);
		glBindVertexArray(0);
		ParticleShader::inst()->projection.loadMatrix4(projection);
	}

	void ParticleRenderer::render(const std::unordered_map<ParticleTexture ,std::shared_ptr<std::list<std::shared_ptr<Particle>>>> & particles, RawCamera & camera)
	{
		prepare();
		auto shader = ParticleShader::inst();
		for (auto &pair : particles) {
			bindTexture(pair.first);
			m_Pointer = 0;
			auto particleList = pair.second;
			std::vector<float> vboData(particleList->size() * INSTANCE_DATA_LENGTH);
			for (auto &particle : *(particleList)) {
				updateModelView(particle->getPosition(), particle->getRotation(), particle->getScale(), camera.getViewMatrix(), vboData);
				updateTexCoordInfo(*particle, vboData);
			}
			m_Loader.updateVbo(m_Vbo, vboData);
			glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, m_Quad.getVertexCount(), particleList->size());
		}
		unbind();
	}

	void ParticleRenderer::prepare()
	{
		ParticleShader::inst()->enable();
		glBindVertexArray(m_Quad.getVaoID());
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		glEnableVertexAttribArray(3);
		glEnableVertexAttribArray(4);
		glEnableVertexAttribArray(5);
		glEnableVertexAttribArray(6);
		glEnable(GL_BLEND);
		glDepthMask(false);
		glDisable(GL_CULL_FACE);
	}

	void ParticleRenderer::bindTexture(const ParticleTexture & texture)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture.getTextureID());
		if (texture.isAdditive())
			glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		else
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		ParticleShader::inst()->numberOfRows.loadFloat(static_cast<float>(texture.getNumberOfRows()));
	}

	void ParticleRenderer::updateModelView(const glm::vec3 & position, float rotation, float scale, const glm::mat4 & view, std::vector<float>& vboData)
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
		storeMatrixDataInVbo(modelView, vboData);
	}

	void ParticleRenderer::updateTexCoordInfo(const Particle & particle, std::vector<float>& data)
	{
		auto &&texOffsetNow = particle.getTexOffsetNow();
		auto &&texOffsetNext = particle.getTexOffsetNext();
		data[m_Pointer++] = texOffsetNow.x;
		data[m_Pointer++] = texOffsetNow.y;
		data[m_Pointer++] = texOffsetNext.x;
		data[m_Pointer++] = texOffsetNext.y;
		data[m_Pointer++] = particle.getBlendFactor();
	}

	void ParticleRenderer::storeMatrixDataInVbo(const glm::mat4 & matrix, std::vector<float>& vboData)
	{
		vboData[m_Pointer++] = matrix[0][0];
		vboData[m_Pointer++] = matrix[0][1];
		vboData[m_Pointer++] = matrix[0][2];
		vboData[m_Pointer++] = matrix[0][3];
		vboData[m_Pointer++] = matrix[1][0];
		vboData[m_Pointer++] = matrix[1][1];
		vboData[m_Pointer++] = matrix[1][2];
		vboData[m_Pointer++] = matrix[1][3];
		vboData[m_Pointer++] = matrix[2][0];
		vboData[m_Pointer++] = matrix[2][1];
		vboData[m_Pointer++] = matrix[2][2];
		vboData[m_Pointer++] = matrix[2][3];
		vboData[m_Pointer++] = matrix[3][0];
		vboData[m_Pointer++] = matrix[3][1];
		vboData[m_Pointer++] = matrix[3][2];
		vboData[m_Pointer++] = matrix[3][3];
	}

	void ParticleRenderer::unbind()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
		glEnable(GL_CULL_FACE);
		glDepthMask(true);
		glDisable(GL_BLEND);
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
		glDisableVertexAttribArray(3);
		glDisableVertexAttribArray(4);
		glDisableVertexAttribArray(5);
		glDisableVertexAttribArray(6);
		glBindVertexArray(0);
		ParticleShader::inst()->disable();
	}

} }
