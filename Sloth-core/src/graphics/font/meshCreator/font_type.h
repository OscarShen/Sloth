/************************************************************************ 
 * @project 	:  sloth
 * @class   	:  FontType
 * @version 	:  v1.0.0
 * @description :  �洢����������������ļ�
 * @author		:  Oscar Shen
 * @creat 		:  2017��2��27��21:30:07
 * @revise 		:  
************************************************************************ 
 * Copyright @ OscarShen 2017. All rights reserved. 
************************************************************************/  
#pragma once
#ifndef SLOTH_FONT_TYPE_HPP
#define SLOTH_FONT_TYPE_HPP

#include <memory>
#include "gui_text.h"
#include "text_mesh_data.hpp"
#include "text_mesh_creator.h"
namespace sloth { namespace graphics {

	class TextMeshCreator;
	class TextMeshData;
	class GUIText;

	class FontType
	{
	private:
		unsigned int m_TexAtlas;
		std::shared_ptr<TextMeshCreator> m_Loader;

	public:
		/***********************************************************************
		* @description	: ��ʼ�����洢����������������ļ�
		* @author		: Oscar Shen
		* @creat		: 2017��2��27��21:22:59
		***********************************************************************/
		FontType(unsigned int texAtlas, const std::string &fontFilePath);

		~FontType() {}

		/***********************************************************************
		* @description	: ��������λͼ����
		* @author		: Oscar Shen
		* @creat		: 2017��2��27��21:27:10
		***********************************************************************/
		inline unsigned int getTextureAtlas() const { return m_TexAtlas; }

		/***********************************************************************
		* @description	: ����ָ�����ı�������ƬԪ����
		* @author		: Oscar Shen
		* @creat		: 2017��2��27��21:29:07
		***********************************************************************/
		std::shared_ptr<TextMeshData> loadText(std::shared_ptr<GUIText> text);
	};
} }



#endif // !SLOTH_FONT_TYPE_HPP
