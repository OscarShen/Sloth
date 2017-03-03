#include "test_renderer.h"

namespace sloth { namespace graphics {

	TestRenderer::TestRenderer(glm::mat4 & projection)
	{
		TestShader::inst()->loadProjection(projection);
	}

	void TestRenderer::render(Entity & entity)
	{
		prepareTexturedModel(entity.getTexturedModel());
		prepareInstance(entity);
		glDrawArrays(GL_TRIANGLES, 0, entity.getTexturedModel().getRawModel().getVertexCount());
		glBindTexture(GL_TEXTURE_2D, 0);
		unbindTexturedModel();
	}

	void TestRenderer::prepareTexturedModel(const TexturedModel & model) const
	{
		TestShader::inst()->use();
		auto &rawModel = model.getRawModel();
		auto &texture = model.getTexture();
		glBindVertexArray(rawModel.getVaoID());
		auto shader = TestShader::inst();
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture.getID());
	}

	void TestRenderer::prepareInstance(Entity & entity)
	{
		auto texture = entity.getTexturedModel().getTexture();
		auto shader = TestShader::inst();
		shader->loadModel(util::Maths::createModelMatrix(entity.getPosition(),
			entity.getRotX(), entity.getRotY(), entity.getRotZ(), entity.getScale()));
	}

	void TestRenderer::unbindTexturedModel()
	{
		glBindVertexArray(0);
		glEnable(GL_CULL_FACE);
	}


} }