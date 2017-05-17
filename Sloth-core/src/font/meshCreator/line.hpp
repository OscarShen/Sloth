/************************************************************************ 
 * @project 	:  sloth
 * @class   	:  Line
 * @version 	:  v1.0.0
 * @description :  存储一行文字
 * @author		:  Oscar Shen
 * @creat 		:  2017年2月27日21:42:05
 * @revise 		:  
************************************************************************ 
 * Copyright @ OscarShen 2017. All rights reserved. 
************************************************************************/  
#pragma once
#ifndef SLOTH_LINE_HPP
#define SLOTH_LINE_HPP

#include <sloth.h>
#include "word.hpp"
namespace sloth {

	class Line
	{
	private:
		double m_MaxLength;
		double m_SpaceSize;
		std::shared_ptr<std::vector<std::shared_ptr<Word>>> m_Words;
		double m_CurrentLineLength = 0.0;

	public:
		Line(double spaceWidth, double fontSize, double maxLength)
			:m_SpaceSize(spaceWidth * fontSize), m_MaxLength(maxLength),
			m_Words(new std::vector<std::shared_ptr<Word>>) {}

		/***********************************************************************
		* @description	: 尝试在本行增加单词，如果长度不够则加载失败
		* @author		: Oscar Shen
		* @creat		: 2017年2月27日21:39:26
		***********************************************************************/
		bool tryToAddWord(std::shared_ptr<Word> word)
		{
			double anotherLength = word->getWordWidth();
			anotherLength += m_Words->empty() ? 0 : m_SpaceSize;
			if (m_CurrentLineLength + anotherLength <= m_MaxLength) {
				m_Words->push_back(word);
				m_CurrentLineLength += anotherLength;
				return true;
			}
			return false;
		}

		inline double getMaxLength() const { return m_MaxLength; }
		inline double getLineLength() const { return m_CurrentLineLength; }
		inline std::shared_ptr<std::vector<std::shared_ptr<Word>>> getWords() { return m_Words; }
	};
}


#endif // !SLOTH_LINE_HPP
