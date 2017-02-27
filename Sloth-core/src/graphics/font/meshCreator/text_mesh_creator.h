/************************************************************************ 
 * @project 	:  sloth
 * @class   	:  TextMeshCreator
 * @version 	:  v1.0.0
 * @description :  �ı�ƬԪ������
 * @author		:  Oscar Shen
 * @creat 		:  2017��2��27��21:49:39
 * @revise 		:  
************************************************************************ 
 * Copyright @ OscarShen 2017. All rights reserved. 
************************************************************************/  
#pragma once
#ifndef SLOTH_TEXT_MESH_CREATOR_H_
#define SLOTH_TEXT_MESH_CREATOR_H_

#include <memory>
#include "line.hpp"
#include "meta_file.h"
#include "gui_text.h"
#include "text_mesh_data.hpp"

namespace sloth { namespace graphics {

#define TEXT_LINE_HEIGHT 0.03
#define TEXT_SPACE_ASCII 32

	class MetaFile;
	class GUIText;
	class TextMeshData;

	class TextMeshCreator
	{
	private:
		std::shared_ptr<MetaFile> m_MetaData;

	public:
		TextMeshCreator(const std::string &filePath);

		/***********************************************************************
		* @description	: ʹ���趨�õ� GUIText ����ƬԪ����
		* @author		: Oscar Shen
		* @creat		: 2017��2��27��21:39:26
		***********************************************************************/
		std::shared_ptr<TextMeshData> createTextMesh(std::shared_ptr<GUIText> text);

	private:
		/***********************************************************************
		* @description	: ������������ṹ��������
		* @author		: Oscar Shen
		* @creat		: 2017��2��27��21:39:26
		***********************************************************************/
		std::shared_ptr<std::vector<std::shared_ptr<Line>>> createStructure(std::shared_ptr<GUIText> text);

		/***********************************************************************
		* @description	: �����һ�����ʼ�������
		* @author		: Oscar Shen
		* @creat		: 2017��2��27��21:39:26
		***********************************************************************/
		void completeStructure(std::shared_ptr<std::vector<std::shared_ptr<Line>>> lines, std::shared_ptr<Line> currentLine, std::shared_ptr<Word> currentWord, std::shared_ptr<GUIText> text);

		/***********************************************************************
		* @description	: ������Ⱦ���巽��Ķ����Լ���������
		* @author		: Oscar Shen
		* @creat		: 2017��2��27��21:39:26
		***********************************************************************/
		std::shared_ptr<TextMeshData> createQuadVertices(std::shared_ptr<GUIText> text, std::shared_ptr<std::vector<std::shared_ptr<Line>>> lines);

		/***********************************************************************
		* @description	: Ϊÿһ���ַ��Ķ���׼������
		* @author		: Oscar Shen
		* @creat		: 2017��2��27��21:39:26
		***********************************************************************/
		void addVerticesForCharacter(double cursorX, double cursorY, std::shared_ptr<Character> character,
			double fontSize, std::shared_ptr<std::vector<float>> vertices);

		/***********************************************************************
		* @description	: ������λ�üӵ�������
		* @author		: Oscar Shen
		* @creat		: 2017��2��27��21:39:26
		***********************************************************************/
		static void addVertices(std::shared_ptr<std::vector<float>> vertices, double x, double y, double maxX, double maxY);

		/***********************************************************************
		* @description	: ����������ӵ�������
		* @author		: Oscar Shen
		* @creat		: 2017��2��27��21:39:26
		***********************************************************************/
		static void addTexCoords(std::shared_ptr<std::vector<float>> texCoords, double x, double y, double maxX, double maxY);
	};

	//typedef typename std::shared_ptr<TextMeshCreator> TextMeshCreator_s;
} }


#endif // !SLOTH_TEXT_MESH_CREATOR_H_
