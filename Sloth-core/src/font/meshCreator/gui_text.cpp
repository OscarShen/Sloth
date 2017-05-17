#include "gui_text.h"
#include "font_type.h"
#include "../fontRenderer/text_master.h"
namespace sloth {
	GUIText::GUIText(const std::string &text, float fontSize, std::shared_ptr<FontType> font, const glm::vec2 & position, float maxLineLength, bool centered)
		:m_TextString(text), m_FontSize(fontSize), m_Font(font), m_Position(position), m_LineMaxSize(maxLineLength), m_CenterText(centered)
	{
	}

} 
