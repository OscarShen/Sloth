/************************************************************************ 
 * @project 	:  $rootnamespace$
 * @class   	:  $safeitemrootname$
 * @version 	:  v1.0.0
 * @description :  
 * @author		:  $username$
 * @creat 		:  $time$
 * @revise 		:  $time$
************************************************************************ 
 * Copyright @ OscarShen 2017. All rights reserved. 
************************************************************************/  
#pragma once
#ifndef SLOTH_WORD_HPP
#define SLOTH_WORD_HPP

#include <sloth.h>
#include "character.hpp"

namespace sloth {

	class Word
	{
	private:
		std::shared_ptr<std::vector<std::shared_ptr<Character>>> m_Characters;
		double m_Width = 0.0;
		double m_FontSize;

	public:
		/***********************************************************************
		* @description	: �洢һ������
						  fontSize : �����С
		* @author		: Oscar Shen
		* @creat		: 2017��2��22��20:05:48
		***********************************************************************/
		Word(double fontSize) 
			:m_FontSize(fontSize), m_Characters(new std::vector<std::shared_ptr<Character>>) {}

		/***********************************************************************
		* @description	: �ڵ���β������һ���ַ�
		* @author		: Oscar Shen
		* @creat		: 2017��2��22��20:06:06
		***********************************************************************/
		void addCharacter(std::shared_ptr<Character> character)
		{
			m_Characters->push_back(character);
			m_Width += character->getXAdvance() * m_FontSize;
		}

		inline std::shared_ptr<std::vector<std::shared_ptr<Character>>> getCharacters() const { return m_Characters; }

		inline double getWordWidth() const { return m_Width; }
	};
}

#endif // !SLOTH_WORD_HPP
