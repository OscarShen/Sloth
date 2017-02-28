/************************************************************************ 
 * @project 	:  sloth
 * @class   	:  FontRenderer
 * @version 	:  v1.0.0
 * @description :  font ����Ⱦ������
 * @author		:  Oscar Shen
 * @creat 		:  2017��2��28��09:56:25
 * @revise 		:  
************************************************************************ 
 * Copyright @ OscarShen 2017. All rights reserved. 
************************************************************************/  
#pragma once
#ifndef SLOTH_FONT_RENDERER_H_
#define SLOTH_FONT_RENDERER_H_

#include "../meshCreator/font_type.h"
#include "../meshCreator/gui_text.h"
#include "font_shader.h"
#include <unordered_map>
#include <memory>
namespace sloth { namespace graphics {

	class FontType;
	class GUIText;
	class FontRenderer
	{
	public:
		FontRenderer() {}

		/***********************************************************************
		* @description	: ��Ⱦ������������������� GUIText
		* @author		: Oscar Shen
		* @creat		: 2017��2��28��09:57:43
		***********************************************************************/
		void render(const std::unordered_map<std::shared_ptr<FontType>,
			std::shared_ptr<std::vector<std::shared_ptr<GUIText>>>> &texts);

	private:
		void prepareRender();
		void unbind();

		/***********************************************************************
		* @description	: ��Ⱦָ���� GUIText
		* @author		: Oscar Shen
		* @creat		: 2017��2��28��09:58:05
		***********************************************************************/
		void renderText(std::shared_ptr<GUIText> text);
	};

} }


#endif // !SLOTH_FONT_RENDERER_H_
