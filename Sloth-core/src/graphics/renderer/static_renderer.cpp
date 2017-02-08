#include "static_renderer.h"

namespace sloth { namespace graphics {

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
		TextureManager2D::inst()->unbindTexture();
		unbindTexturedModel();
	}

	void StaticRenderer::render(std::map<TexturedModel, std::vector<Entity>> &entities)
	{
		StaticShader::inst()->use();
		for (auto it = entities.begin(); it != entities.end(); ++it) {
			prepareTexturedModel(it->first);
			std::vector<Entity> &batch = entities[it->first];
			for (auto it2 = batch.begin(); it2 != batch.end(); ++it2) {
				prepareInstance(*it2);
				glDrawElements(GL_TRIANGLES, it->first.getRawModel().getVertexCount(), GL_UNSIGNED_INT, nullptr);
			}
			TextureManager2D::inst()->unbindTexture();
			unbindTexturedModel();
		}
	}

	void StaticRenderer::prepareTexturedModel(const TexturedModel & model)
	{
		TextureManager2D *tm = TextureManager2D::inst();
		RawModel rawModel = model.getRawModel();
		Texture2D *texture = tm->getTexture(model.getTexID());
		glBindVertexArray(rawModel.getVaoID());
		auto shader = StaticShader::inst();
		shader->loadNumberOfRows(texture->getNumberOfRows());
		if (texture->hasTransparency()) {
			disable_culling();
		}
		shader->loadUseFakeLighting(texture->isUseFakeLighting());
		tm->activateTexUnit(0);
		tm->bindTexture(model.getTexID());
	}

	void StaticRenderer::prepareInstance(Entity & entity)
	{
		auto texture = entity.getTexturedModel().getTexture();
		auto shader = StaticShader::inst();
		shader->loadModelMatrix(util::Maths::createModelMatrix(entity.getPosition(),
			entity.getRotX(), entity.getRotY(), entity.getRotZ(), entity.getScale()));
		shader->loadShineVariable(texture->getShininess(), texture->getReflectivity());
		shader->loadOffset(entity.getTextureXOffset(), entity.getTextureYOffset());
	}

	void StaticRenderer::unbindTexturedModel()
	{
		glBindVertexArray(0);
		enable_culling();
	}

} }
