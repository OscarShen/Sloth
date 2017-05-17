/************************************************************************ 
 * @project 	:  sloth
 * @class   	:  TextMaster
 * @version 	:  v1.0.0
 * @description :  文本渲染控制类——控制 FontRenderer 进行渲染
 * @author		:  Oscar Shen
 * @creat 		:  2017年2月28日09:53:43
 * @revise 		:  
************************************************************************ 
 * Copyright @ OscarShen 2017. All rights reserved. 
************************************************************************/  
#pragma once
#ifndef SLOTH_TEXT_MASTER_H_
#define SLOTH_TEXT_MASTER_H_

#include <sloth.h>
namespace sloth {

	class FontType;
	class GUIText;
	class FontRenderer;
	class Loader;
	class TextMaster
	{
	private:
		Loader &m_Loader;
		std::unordered_map<std::shared_ptr<FontType>, 
			std::shared_ptr<std::vector<std::shared_ptr<GUIText>>>> m_Texts;
		std::shared_ptr<FontRenderer> m_Renderer;

	public:
		TextMaster(Loader &loader);

		/***********************************************************************
		* @description	: 使用已经加载好的数据控制 FontRenderer 进行渲染
		* @author		: Oscar Shen
		* @creat		: 2017年2月28日09:50:46
		***********************************************************************/
		void render();

		/***********************************************************************
		* @description	: 预加载指定的文本
		* @author		: Oscar Shen
		* @creat		: 2017年2月28日09:52:07
		***********************************************************************/
		void loadText(std::shared_ptr<GUIText> text);

		/***********************************************************************
		* @description	: 删除加载的文本
		* @author		: Oscar Shen
		* @creat		: 2017年2月28日09:53:00
		***********************************************************************/
		void removeText(std::shared_ptr<GUIText> text);
	};

}



#endif // !SLOTH_TEXT_MASTER_H_
