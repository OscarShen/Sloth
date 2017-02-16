#include "gui_renderer.h"

namespace sloth { namespace graphics {
	GuiRenderer::GuiRenderer(Loader &loader)
	{
		// GUI矩形的四个点
		//float positions[]{
		//	-1.0f, 1.0f,
		//	-1.0f,-1.0f,
		//	 1.0f, 1.0f,
		//	 1.0f,-1.0f
		//};
		std::vector<glm::vec2> positions;
		std::vector<glm::vec2> texCoord;
		positions.push_back(glm::vec2(-1.0f,  1.0f));
		texCoord.push_back(glm::vec2(0.0f, 0.0f));
		positions.push_back(glm::vec2(-1.0f, -1.0f));
		texCoord.push_back(glm::vec2(0.0f, 1.0f));
		positions.push_back(glm::vec2( 1.0f,  1.0f));
		texCoord.push_back(glm::vec2(1.0f, 0.0f));
		positions.push_back(glm::vec2( 1.0f, -1.0f));
		texCoord.push_back(glm::vec2(1.0f, 1.0f));
		m_Quad = loader.loadToVAO(positions, texCoord);
	}

	void GuiRenderer::render(std::vector<GuiTexture>& guis)
	{
		GuiShader::inst()->enable();
		glBindVertexArray(m_Quad.getVaoID());
		glEnableVertexArrayAttrib(m_Quad.getVaoID(), 0);
		glEnableVertexArrayAttrib(m_Quad.getVaoID(), 1);
		// 开启混合模式，a 分量不等于 1.0 的像素不进行渲染
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		// 关闭深度测试，因为深度测试会影响会相互覆盖，即使 a 分量不为 1.0
		glDisable(GL_DEPTH_TEST);
		for (auto it = guis.begin(); it != guis.end(); ++it) {
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, it->getID());
			glm::mat4 mat = util::Maths::createModelMatrix(it->getPosition(), it->getScale());
			GuiShader::inst()->loadTransformation(mat);
			glDrawArrays(GL_TRIANGLE_STRIP, 0, m_Quad.getVertexCount());
 		}
		glEnable(GL_DEPTH_TEST);
		glDisable(GL_BLEND);
		glDisableVertexArrayAttrib(m_Quad.getVaoID(), 0);
		glDisableVertexArrayAttrib(m_Quad.getVaoID(), 1);
		glBindVertexArray(0);
		GuiShader::inst()->disable();
	}

} }
