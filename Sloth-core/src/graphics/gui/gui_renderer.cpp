#include "gui_renderer.h"

namespace sloth { namespace graphics {
	GuiRenderer::GuiRenderer(Loader &loader)
	{
		// GUI���ε��ĸ���
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
		// �������ģʽ��a ���������� 1.0 �����ز�������Ⱦ
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		// �ر���Ȳ��ԣ���Ϊ��Ȳ��Ի�Ӱ����໥���ǣ���ʹ a ������Ϊ 1.0
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
