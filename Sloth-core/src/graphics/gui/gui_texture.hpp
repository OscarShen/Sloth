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
		unsigned int m_ID;
		glm::vec2 m_Position;
		glm::vec2 m_Scale;

	public:
		constexpr GuiTexture(
			unsigned int id,
			const glm::vec2 &position,
			const glm::vec2 &scale
		) :m_ID(id), m_Position(position), m_Scale(scale) {}
		~GuiTexture() {}
		
		inline unsigned int getID() const { return m_ID; }
		inline glm::vec2 getPosition() const { return m_Position; }
		inline glm::vec2 getScale() const { return m_Scale; }
	};

} }

#endif // !SLOTH_GUI_TEXTURE
