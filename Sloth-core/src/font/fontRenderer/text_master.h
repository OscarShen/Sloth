/************************************************************************ 
 * @project 	:  sloth
 * @class   	:  TextMaster
 * @version 	:  v1.0.0
 * @description :  �ı���Ⱦ�����ࡪ������ FontRenderer ������Ⱦ
 * @author		:  Oscar Shen
 * @creat 		:  2017��2��28��09:53:43
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
		* @description	: ʹ���Ѿ����غõ����ݿ��� FontRenderer ������Ⱦ
		* @author		: Oscar Shen
		* @creat		: 2017��2��28��09:50:46
		***********************************************************************/
		void render();

		/***********************************************************************
		* @description	: Ԥ����ָ�����ı�
		* @author		: Oscar Shen
		* @creat		: 2017��2��28��09:52:07
		***********************************************************************/
		void loadText(std::shared_ptr<GUIText> text);

		/***********************************************************************
		* @description	: ɾ�����ص��ı�
		* @author		: Oscar Shen
		* @creat		: 2017��2��28��09:53:00
		***********************************************************************/
		void removeText(std::shared_ptr<GUIText> text);
	};

}



#endif // !SLOTH_TEXT_MASTER_H_
