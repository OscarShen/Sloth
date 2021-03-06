#include "static_renderer.h"

namespace sloth { 

	StaticRenderer::StaticRenderer(glm::mat4 & projection)
	{
		StaticShader::inst()->loadProjectionMatrix(projection);
	}

	void StaticRenderer::render(Entity & entity)
	{
		StaticShader::inst()->use();
		prepareTexturedModel(entity.getTexturedModel());
		prepareInstance(entity);
		glDrawElements(GL_TRIANGLES, entity.getTexturedModel().getRawModel().getVertexCount(), GL_UNSIGNED_INT, nullptr);
		glBindTexture(GL_TEXTURE_2D, 0);
		unbindTexturedModel();
	}

	void StaticRenderer::render(MapedEntities &entities)
	{
		StaticShader::inst()->enable();
		for (auto it = entities.begin(); it != entities.end(); ++it) {
			prepareTexturedModel(it->first);
			auto &batch = entities[it->first];
			for (auto it2 = batch.begin(); it2 != batch.end(); ++it2) {
				prepareInstance(**it2);
				glDrawElements(GL_TRIANGLES, it->first.getRawModel().getVertexCount(), GL_UNSIGNED_INT, nullptr);
			}
			glBindTexture(GL_TEXTURE_2D, 0);
			unbindTexturedModel();
		}
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
		StaticShader::inst()->disable();
	}

	void StaticRenderer::prepareTexturedModel(const TexturedModel & model) const
	{
		auto &rawModel = model.getRawModel();
		auto &texture = model.getTexture();
		glBindVertexArray(rawModel.getVaoID());
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		auto shader = StaticShader::inst();
		shader->loadNumberOfRows(texture.getNumberOfRows());
		if (texture.hasTransparency()) {
			glDisable(GL_CULL_FACE);
		}
		shader->loadUseFakeLighting(texture.isUseFakeLighting());
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture.getID());
		if (texture.hasSpecularMap()) {
			glActiveTexture(GL_TEXTURE2);
			glBindTexture(GL_TEXTURE_2D, texture.getSpecularMap());
		}
		shader->loadUseSpecularMap(texture.hasSpecularMap());
		//shader->loadUseSpecularMap(false);

	}

	void StaticRenderer::prepareInstance(Entity & entity)
	{
		auto texture = entity.getTexturedModel().getTexture();
		auto shader = StaticShader::inst();
		shader->loadModelMatrix(Maths::createModelMatrix(entity.getPosition(),
			entity.getRotX(), entity.getRotY(), entity.getRotZ(), entity.getScale()));
		shader->loadShineVariable(texture.getShininess(), texture.getReflectivity());
		shader->loadOffset(entity.getTextureXOffset(), entity.getTextureYOffset());
	}

	void StaticRenderer::unbindTexturedModel()
	{
		glBindVertexArray(0);
		glEnable(GL_CULL_FACE);
	}

} 
