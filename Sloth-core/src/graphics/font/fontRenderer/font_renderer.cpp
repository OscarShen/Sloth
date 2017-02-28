#include "font_renderer.h"

void sloth::graphics::FontRenderer::render(const std::unordered_map<std::shared_ptr<FontType>, std::shared_ptr<std::vector<std::shared_ptr<GUIText>>>>& texts)
{
	prepareRender();
	for (auto &font_pair : texts) {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, font_pair.first->getTextureAtlas());
		for (auto &text : *font_pair.second) {
			renderText(text);
		}
	}
	unbind();
}

void sloth::graphics::FontRenderer::prepareRender()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_DEPTH_TEST);
	FontShader::inst()->enable();
}

void sloth::graphics::FontRenderer::unbind()
{
	FontShader::inst()->disable();
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
}

void sloth::graphics::FontRenderer::renderText(std::shared_ptr<GUIText> text)
{
	auto shader = FontShader::inst();
	glBindVertexArray(text->getMeshVAO());
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	shader->loadColor(text->getColor());
	shader->loadModel(text->getPosition());
	glDrawArrays(GL_TRIANGLES, 0, text->getVertexCount());

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glBindVertexArray(0);
}
