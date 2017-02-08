#pragma once
#ifndef SLOTH_GUI_TEXTURE
#define SLOTH_GUI_TEXTURE

#include <glm/glm.hpp>
namespace sloth { namespace graphics {

	// GuiTexture 专用于 GUI 纹理，相对普通纹理少了很多
	// 要素，资源的开辟和释放由 TextureManage 来管理
	class GuiTexture
	{
	private:
		unsigned int m_TexID;
		glm::vec2 m_Position;
		glm::vec2 m_Scale;

	public:
		constexpr GuiTexture(
			unsigned int texID,
			const glm::vec2 &position,
			const glm::vec2 &scale
		) :m_TexID(texID), m_Position(position), m_Scale(scale) {}
		~GuiTexture() {}
		
		inline unsigned int getTexID() const { return m_TexID; }
		inline glm::vec2 getPosition() const { return m_Position; }
		inline glm::vec2 getScale() const { return m_Scale; }
	};

} }

#endif // !SLOTH_GUI_TEXTURE
