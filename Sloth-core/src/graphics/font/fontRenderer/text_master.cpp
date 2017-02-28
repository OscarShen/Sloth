#include "text_master.h"

namespace sloth { namespace graphics {
	TextMaster::TextMaster(Loader & loader)
		:m_Loader(loader), m_Renderer(std::shared_ptr<FontRenderer>(new FontRenderer()))
	{
	}

	void TextMaster::render()
	{
		m_Renderer->render(m_Texts);
	}

	void TextMaster::loadText(std::shared_ptr<GUIText> text)
	{
		std::shared_ptr<FontType> font = text->getFont();
		std::shared_ptr<TextMeshData> data = font->loadText(text);
		int vao = m_Loader.loadToVAO(*data->getVertexPositions(), *data->getTexCoords());
		text->setMeshInfo(vao, data->getVertexCount());
		auto it = m_Texts.find(font);
		std::shared_ptr<std::vector<std::shared_ptr<GUIText>>> textBatch;
		if (it == m_Texts.end()) {
			textBatch = std::shared_ptr<std::vector<std::shared_ptr<GUIText>>>(new std::vector<std::shared_ptr<GUIText>>());
			m_Texts[font] = textBatch;
		}
		textBatch->push_back(text);
	}

	void TextMaster::removeText(std::shared_ptr<GUIText> text)
	{
		auto it = m_Texts.find(text->getFont());
		if (it != m_Texts.end()) {
			auto &textBatch = it->second;
			for (auto it2 = textBatch->begin(); it2 != textBatch->end(); ++it2) {
				if (*it2 == text) {
					textBatch->erase(it2);
				}
			}
			if (textBatch->empty()) {
				m_Texts.erase(text->getFont());
			}
		}
	}

} }
