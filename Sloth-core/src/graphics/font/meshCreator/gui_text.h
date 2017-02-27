/************************************************************************ 
 * @project 	:  sloth
 * @class   	:  GUIText
 * @version 	:  v1.0.0
 * @description :  存储渲染所需要的文本纹理、大小、顶点数组、顶点数量、颜色、位置、
				   每行最大长度、行数、中心化数据
 * @author		:  Oscar Shen
 * @creat 		:  2017年2月27日21:36:24
 * @revise 		:  
************************************************************************ 
 * Copyright @ OscarShen 2017. All rights reserved. 
************************************************************************/  
#pragma once
#ifndef SLOTH_GUI_TEXT_HPP
#define SLOTH_GUI_TEXT_HPP

#include <string>
#include <memory>
#include <glm/glm.hpp>
#include "font_type.h"
#include "../fontRenderer/text_master.h"

namespace sloth { namespace graphics {

	class FontType;

	class GUIText
	{
	private:
		std::string m_TextString;
		float m_FontSize;
		unsigned int m_TextMeshVao;
		unsigned int m_VertexCount;
		glm::vec3 m_Color = glm::vec3(0.0f);

		glm::vec2 m_Position;
		float m_LineMaxSize;
		unsigned int m_NumberOfLines;

		std::shared_ptr<FontType> m_Font;
		bool m_CenterText = false;

	public:
		/***********************************************************************
		* @description	: 初始化
						  text : 需要渲染的文本
						  fontSize : 渲染字体的大小
						  position : 渲染字体的左上角位置，此坐标为纹理坐标
						  maxLineLength : 渲染字体一行的最大长度
						  centered : 是否中心对其
		* @author		: Oscar Shen
		* @creat		: 2017年2月27日21:39:26
		***********************************************************************/
		GUIText(const std::string &text, float fontSize, std::shared_ptr<FontType> font, const glm::vec2 &position, float maxLineLength, bool centered);

		/***********************************************************************
		* @description	: 返回字体信息
		* @author		: Oscar Shen
		* @creat		: 2017年2月27日21:39:26
		***********************************************************************/
		inline std::shared_ptr<FontType> getFont() const { return m_Font; }

		/***********************************************************************
		* @description	: 设置字体颜色
		* @author		: Oscar Shen
		* @creat		: 2017年2月27日21:40:02
		***********************************************************************/
		inline void setColor(const glm::vec3 &color) { m_Color = color; }

		/***********************************************************************
		* @description	: 返回字体渲染顶点数组和顶点数目
		* @author		: Oscar Shen
		* @creat		: 2017年2月27日21:39:26
		***********************************************************************/
		inline void setMeshInfo(int vao, int verticesCount)
		{
			m_TextMeshVao = vao;
			m_VertexCount = verticesCount;
		}

		/***********************************************************************
		* @description	: 设置行数
		* @author		: Oscar Shen
		* @creat		: 2017年2月27日21:39:26
		***********************************************************************/
		inline void setNumberOfLines(unsigned int number) { m_NumberOfLines = number; }

		inline glm::vec3 getColor() const { return m_Color; }
		inline unsigned int getNumberOfLines()const { return m_NumberOfLines; }
		inline glm::vec2 getPosition() const { return m_Position; }
		inline unsigned int getMeshVAO() const { return m_TextMeshVao; }
		inline unsigned int getVertexCount() const { return m_VertexCount; }
		inline float getFontSize() const { return m_FontSize; }
		inline bool isCentered() const { return m_CenterText; }
		inline float getMaxLineSize() { return m_LineMaxSize; }
		inline std::string getTextString() const { return m_TextString; }
	};
} }

#endif // !SLOTH_GUI_TEXT_HPP
