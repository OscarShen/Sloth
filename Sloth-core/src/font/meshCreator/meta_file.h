/************************************************************************ 
 * @project 	:  sloth
 * @class   	:  MetaFile
 * @version 	:  v1.0.0
 * @description :  存储字体文件加载后的信息
 * @author		:  Oscar Shen
 * @creat 		:  2017年2月27日21:43:56
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
		* @description	: 返回空格宽度
		* @author		: Oscar Shen
		* @creat		: 2017年2月27日21:39:26
		***********************************************************************/
		double getSpaceWidth() const { return m_SpaceWidth; }

		/***********************************************************************
		* @description	: 用 ascii 码获取 Character 数据
		* @author		: Oscar Shen
		* @creat		: 2017年2月27日21:39:26
		***********************************************************************/
		std::shared_ptr<Character> getCharacter(int ascii) const { return m_MetaData.find(ascii)->second; }

	private:
		/***********************************************************************
		* @description	: 将字体配置文件加载到流中
		* @author		: Oscar Shen
		* @creat		: 2017年2月27日21:45:15
		***********************************************************************/
		void openFile(const std::string &file_path);

		/***********************************************************************
		* @description	: 关闭流
		* @author		: Oscar Shen
		* @creat		: 2017年2月27日21:39:26
		***********************************************************************/
		void close();

		/***********************************************************************
		* @description	: 获取加载的字体边框冗余
		* @author		: Oscar Shen
		* @creat		: 2017年2月27日21:39:26
		***********************************************************************/
		void loadPaddingData();

		/***********************************************************************
		* @description	: 将流中数据的下一行加载到表格中
		* @author		: Oscar Shen
		* @creat		: 2017年2月27日21:39:26
		***********************************************************************/
		bool processNextLine();

		/***********************************************************************
		* @description	: 使用变量名获得对应的多个值
		* @author		: Oscar Shen
		* @creat		: 2017年2月27日21:39:26
		***********************************************************************/
		std::shared_ptr<std::vector<int>> getValuesOfVariable(std::string &variable);

		/***********************************************************************
		* @description	: 使用变量名获得对应的单个值
		* @author		: Oscar Shen
		* @creat		: 2017年2月27日21:39:26
		***********************************************************************/
		int getValueOfVariable(std::string &variable);

		/***********************************************************************
		* @description	: 获取每一行占用的屏幕空间的高度
		* @author		: Oscar Shen
		* @creat		: 2017年2月27日21:39:26
		***********************************************************************/
		void loadLineSizes();

		/***********************************************************************
		* @description	: 加载每一个字符数据
		* @author		: Oscar Shen
		* @creat		: 2017年2月27日21:39:26
		***********************************************************************/
		void loadCharacterData(int imageWidth);

		/***********************************************************************
		* @description	: 用已经加载的字符数据生成 Character 变量
		* @author		: Oscar Shen
		* @creat		: 2017年2月27日21:49:00
		***********************************************************************/
		std::shared_ptr<Character> loadCharacter(int imageSize);
	};
}\


#endif // !SLOTH_META_FILE_H_
