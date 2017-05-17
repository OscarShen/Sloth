#include "font_type.h"
#include "gui_text.h"
#include "text_mesh_data.hpp"
#include "text_mesh_creator.h"
namespace sloth {
	FontType::FontType(unsigned int texAtlas, const std::string & fontFilePath)
		:m_TexAtlas(texAtlas)
	{
		m_Loader = std::shared_ptr<TextMeshCreator>(new TextMeshCreator(fontFilePath));
	}

	std::shared_ptr<TextMeshData> FontType::loadText(std::shared_ptr<GUIText> text)
	{
		return m_Loader->createTextMesh(text);
	}

} 