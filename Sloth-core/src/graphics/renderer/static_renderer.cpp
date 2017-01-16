#include "static_renderer.h"

namespace sloth { namespace graphics {

	StaticRenderer::StaticRenderer(StaticShader * shader)
		:m_Shader(shader) {}

	void StaticRenderer::render(Entity & entity)
	{
		prepareTexturedModel(entity.getTexturedModel());
		prepareInstance(entity);
		glDrawElements(GL_TRIANGLES, entity.getTexturedModel().getRawModel().getVertexCount(), GL_UNSIGNED_INT, nullptr);
		TextureManager2D::inst()->unbindTexture();
	}

	void StaticRenderer::render(std::map<TexturedModel, std::vector<Entity>> &entities)
	{
		for (auto it = entities.begin(); it != entities.end(); ++it) {
			prepareTexturedModel(it->first);
			std::vector<Entity> &batch = entities[it->first];
			for (auto it2 = batch.begin(); it2 != batch.end(); ++it2) {
				prepareInstance(*it2);
				glDrawElements(GL_TRIANGLES, it->first.getRawModel().getVertexCount(), GL_UNSIGNED_INT, nullptr);
			}
			TextureManager2D::inst()->unbindTexture();
		}
	}

	void StaticRenderer::prepareTexturedModel(const TexturedModel & model)
	{
		RawModel rawModel = model.getRawModel();
		glBindVertexArray(rawModel.getVaoID());
		TextureManager2D *tm = TextureManager2D::inst();
		tm->activateTexUnit(0);
		tm->bindTexture(model.getTexID());
	}

	void StaticRenderer::prepareInstance(Entity & entity)
	{
		auto texture = entity.getTexturedModel().getTexture();
		m_Shader->loadModelMatrix(util::Maths::createModelMatrix(entity.getPosition(), entity.getRotX(),
			entity.getRotY(), entity.getRotZ(), entity.getScale()));
		m_Shader->loadShineVariable(texture->getShininess(), texture->getReflectivity());
	}

} }
