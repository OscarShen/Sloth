/************************************************************************ 
 * @project 	:  sloth
 * @class   	:  MetaFile
 * @version 	:  v1.0.0
 * @description :  �洢�����ļ����غ����Ϣ
 * @author		:  Oscar Shen
 * @creat 		:  2017��2��27��21:43:56
 * @revise 		:  
************************************************************************ 
 * Copyright @ OscarShen 2017. All rights reserved. 
************************************************************************/  
#pragma once
#ifndef SLOTH_META_FILE_H_
#define SLOTH_META_FILE_H_
#include <sloth.h>
#include <unordered_map>
namespace sloth {

#define META_FILE_PAD_TOP 0
#define META_FILE_PAD_LEFT 1
#define META_FILE_PAD_BOTTON 2
#define	META_FILE_PAD_RIGHT 3

#define META_FILE_DESIRED_PADDING 10

#define META_FILE_SPLITTER " "
#define META_FILE_NUMBER_SEPARATOR ","
	class Character;
	class MetaFile
	{
	private:
		double m_AspectRatio;
		double m_VerticalPerPixelSize;
		double m_HorizontalPerPixelSize;
		double m_SpaceWidth;
		std::shared_ptr<std::vector<int>> m_Padding;
		unsigned int m_PaddingWidth;
		unsigned int m_PaddingHeight;

		std::unordered_map<int, std::shared_ptr<Character>> m_MetaData;
		std::unordered_map<std::string, std::string> m_Values;
		std::ifstream m_FileStream;

	public:
		MetaFile(const std::string &file_path);

		/***********************************************************************
		* @description	: ���ؿո���
		* @author		: Oscar Shen
		* @creat		: 2017��2��27��21:39:26
		***********************************************************************/
		double getSpaceWidth() const { return m_SpaceWidth; }

		/***********************************************************************
		* @description	: �� ascii ���ȡ Character ����
		* @author		: Oscar Shen
		* @creat		: 2017��2��27��21:39:26
		***********************************************************************/
		std::shared_ptr<Character> getCharacter(int ascii) const { return m_MetaData.find(ascii)->second; }

	private:
		/***********************************************************************
		* @description	: �����������ļ����ص�����
		* @author		: Oscar Shen
		* @creat		: 2017��2��27��21:45:15
		***********************************************************************/
		void openFile(const std::string &file_path);

		/***********************************************************************
		* @description	: �ر���
		* @author		: Oscar Shen
		* @creat		: 2017��2��27��21:39:26
		***********************************************************************/
		void close();

		/***********************************************************************
		* @description	: ��ȡ���ص�����߿�����
		* @author		: Oscar Shen
		* @creat		: 2017��2��27��21:39:26
		***********************************************************************/
		void loadPaddingData();

		/***********************************************************************
		* @description	: ���������ݵ���һ�м��ص������
		* @author		: Oscar Shen
		* @creat		: 2017��2��27��21:39:26
		***********************************************************************/
		bool processNextLine();

		/***********************************************************************
		* @description	: ʹ�ñ�������ö�Ӧ�Ķ��ֵ
		* @author		: Oscar Shen
		* @creat		: 2017��2��27��21:39:26
		***********************************************************************/
		std::shared_ptr<std::vector<int>> getValuesOfVariable(std::string &variable);

		/***********************************************************************
		* @description	: ʹ�ñ�������ö�Ӧ�ĵ���ֵ
		* @author		: Oscar Shen
		* @creat		: 2017��2��27��21:39:26
		***********************************************************************/
		int getValueOfVariable(std::string &variable);

		/***********************************************************************
		* @description	: ��ȡÿһ��ռ�õ���Ļ�ռ�ĸ߶�
		* @author		: Oscar Shen
		* @creat		: 2017��2��27��21:39:26
		***********************************************************************/
		void loadLineSizes();

		/***********************************************************************
		* @description	: ����ÿһ���ַ�����
		* @author		: Oscar Shen
		* @creat		: 2017��2��27��21:39:26
		***********************************************************************/
		void loadCharacterData(int imageWidth);

		/***********************************************************************
		* @description	: ���Ѿ����ص��ַ��������� Character ����
		* @author		: Oscar Shen
		* @creat		: 2017��2��27��21:49:00
		***********************************************************************/
		std::shared_ptr<Character> loadCharacter(int imageSize);
	};
}\


#endif // !SLOTH_META_FILE_H_
