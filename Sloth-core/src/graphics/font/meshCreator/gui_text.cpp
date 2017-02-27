#include "gui_text.h"

namespace sloth { namespace graphics {
	GUIText::GUIText(const std::string &text, float fontSize, std::shared_ptr<FontType> font, const glm::vec2 & position, float maxLineLength, bool centered)
		:m_TextString(text), m_FontSize(fontSize), m_Font(font), m_Position(position), m_LineMaxSize(maxLineLength), m_CenterText(centered)
	{
	}

} }
