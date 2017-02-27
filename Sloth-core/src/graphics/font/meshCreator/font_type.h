/************************************************************************ 
 * @project 	:  sloth
 * @class   	:  FontType
 * @version 	:  v1.0.0
 * @description :  存储着字体纹理和数据文件
 * @author		:  Oscar Shen
 * @creat 		:  2017年2月27日21:30:07
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
		* @description	: 初始化，存储着字体纹理和数据文件
		* @author		: Oscar Shen
		* @creat		: 2017年2月27日21:22:59
		***********************************************************************/
		FontType(unsigned int texAtlas, const std::string &fontFilePath);

		~FontType() {}

		/***********************************************************************
		* @description	: 返回字体位图纹理
		* @author		: Oscar Shen
		* @creat		: 2017年2月27日21:27:10
		***********************************************************************/
		inline unsigned int getTextureAtlas() const { return m_TexAtlas; }

		/***********************************************************************
		* @description	: 加载指定的文本并产生片元数据
		* @author		: Oscar Shen
		* @creat		: 2017年2月27日21:29:07
		***********************************************************************/
		std::shared_ptr<TextMeshData> loadText(std::shared_ptr<GUIText> text);
	};
} }



#endif // !SLOTH_FONT_TYPE_HPP
