/************************************************************************
* @project 		:  sloth
* @class   		:  GuiTexture
* @version 		:  v1.0.0
* @description	:  ������Ⱦ GUI ������
* @author		:  Oscar Shen
* @creat 		:  2017��2��16��10:46:44
* @revise 		:
************************************************************************
* Copyright @ OscarShen 2017. All rights reserved.
************************************************************************/
#pragma once
#ifndef SLOTH_GUI_TEXTURE
#define SLOTH_GUI_TEXTURE

#include <sloth.h>
namespace sloth {

	// GuiTexture ר���� GUI ���������ͨ�������˺ܶ�
	// Ҫ�أ���Դ�Ŀ��ٺ��ͷ��� TextureManage ������
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

}

#endif // !SLOTH_GUI_TEXTURE
