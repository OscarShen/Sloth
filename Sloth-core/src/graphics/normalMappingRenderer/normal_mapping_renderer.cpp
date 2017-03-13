#include "normal_mapping_renderer.h"

namespace sloth { namespace graphics {

	NormalMappingRenderer::NormalMappingRenderer(glm::mat4 & projection)
	{
		NormalMappingShader::inst()->loadProjectionMatrix(projection);
		NormalMappingShader::inst()->connectTextureUnit();
	}

	void NormalMappingRenderer::render(Entity_s & entity)
	{
		NormalMappingShader::inst()->use();
		prepareTexturedModel(entity->getTexturedModel());
		prepareInstance(entity);
		glDrawElements(GL_TRIANGLES, entity->getTexturedModel().getRawModel().getVertexCount(), GL_UNSIGNED_INT, nullptr);
		glBindTexture(GL_TEXTURE_2D, 0);
		unbindTexturedModel();
	}

	void NormalMappingRenderer::render(MapedEntities &entities)
	{
		NormalMappingShader::inst()->enable();
		for (auto it = entities.begin(); it != entities.end(); ++it) {
			prepareTexturedModel(it->first);
			auto &batch = entities[it->first];
			for (auto it2 = batch.begin(); it2 != batch.end(); ++it2) {
				prepareInstance(*it2);
				glDrawElements(GL_TRIANGLES, it->first.getRawModel().getVertexCount(), GL_UNSIGNED_INT, nullptr);
			}
			glBindTexture(GL_TEXTURE_2D, 0);
			unbindTexturedModel();
		}
		NormalMappingShader::inst()->disable();
	}

	void NormalMappingRenderer::prepareTexturedModel(const TexturedModel & model) const
	{
		auto &rawModel = model.getRawModel();
		auto &texture = model.getTexture();
		glBindVertexArray(rawModel.getVaoID());
		auto shader = NormalMappingShader::inst();
		shader->loadNumberOfRows(texture.getNumberOfRows());
		if (texture.hasTransparency()) {
			glDisable(GL_CULL_FACE);
		}
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture.getID());
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture.getNormalMap());

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		glEnableVertexAttribArray(3);
	}

	void NormalMappingRenderer::prepareInstance(Entity_s & entity)
	{
		auto &&texture = entity->getTexturedModel().getTexture();
		auto shader = NormalMappingShader::inst();
		shader->loadModelMatrix(util::Maths::createModelMatrix(entity->getPosition(),
			entity->getRotX(), entity->getRotY(), entity->getRotZ(), entity->getScale()));
		shader->loadShineVariable(texture.getShininess(), texture.getReflectivity());
		shader->loadOffset(entity->getTextureXOffset(), entity->getTextureYOffset());
	}

	void NormalMappingRenderer::unbindTexturedModel()
	{
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
		glDisableVertexAttribArray(3);
		glBindVertexArray(0);
		glEnable(GL_CULL_FACE);
	}

} }
