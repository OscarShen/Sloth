/************************************************************************ 
 * @project 	:  sloth
 * @class   	:  FontShader
 * @version 	:  v1.0.0
 * @description :  ��������ɫ���� uniform �������Ӧ�������޸���ɫ������
 * @author		:  Oscar Shen
 * @creat 		:  2017��2��28��09:55:18
 * @revise 		:  
************************************************************************ 
 * Copyright @ OscarShen 2017. All rights reserved. 
************************************************************************/  
#pragma once
#ifndef SLOTH_FONT_SHADER_H_
#define SLOTH_FONT_SHADER_H_
#include "../../shader/shader.h"
namespace sloth { namespace graphics {

#define FONT_SHADER_VERTEX_FILE "src/graphics/font/fontRenderer/font.vert"
#define FONT_SHADER_FRAGMENT_FILE "src/graphics/font/fontRenderer/font.frag"

	class FontShader : public Shader
	{
	private:
		int m_LocColor; // ������ɫ
		int m_LocModel; // �������ʼλ��
		int m_LocFontWidth; // ����Ŀ��
		int m_LocFontEdge; // ����Ľ�����
		int m_LocBorderWidth; // ��������������
		int m_LocBorderEdge; // �����������Ľ�����
		int m_LocOffset; // �����ƫ��ֵ�����Բ����������Ӱ
		int m_LocOutlineColor; // ��������������ɫ
		static FontShader *m_Inst;

	public:
		static FontShader* inst();

		static void cleanUp();

		/***********************************************************************
		* @description	: ����������ɫ
		* @author		: Oscar Shen
		* @creat		: 2017��3��1��15:58:10
		***********************************************************************/
		void loadColor(const glm::vec3 &color);

		/***********************************************************************
		* @description	: �����������ʼλ��
		* @author		: Oscar Shen
		* @creat		: 2017��3��1��15:58:23
		***********************************************************************/
		void loadModel(const glm::vec2 &model);

		/***********************************************************************
		* @description	: ��������Ŀ��
		* @author		: Oscar Shen
		* @creat		: 2017��3��1��15:58:23
		***********************************************************************/
		void loadFontWidth(float fontWidth);

		/***********************************************************************
		* @description	: ��������Ľ�����
		* @author		: Oscar Shen
		* @creat		: 2017��3��1��15:58:23
		***********************************************************************/
		void loadFontEdge(float fontEdge);

		/***********************************************************************
		* @description	: ������������������
		* @author		: Oscar Shen
		* @creat		: 2017��3��1��15:58:23
		***********************************************************************/
		void loadBorderWidth(float borderWidth);

		/***********************************************************************
		* @description	: ���������������Ľ�����
		* @author		: Oscar Shen
		* @creat		: 2017��3��1��15:58:23�����ƫ��ֵ�����Բ����������Ӱ
		***********************************************************************/
		void loadBorderEdge(float borderEdge);

		/***********************************************************************
		* @description	: ���������ƫ��ֵ�����Բ����������Ӱ
		* @author		: Oscar Shen
		* @creat		: 2017��3��1��15:58:23
		***********************************************************************/
		void loadOffset(const glm::vec2 &offset);

		/***********************************************************************
		* @description	: ������������������ɫ
		* @author		: Oscar Shen
		* @creat		: 2017��3��1��16:00:14
		***********************************************************************/
		void loadOutlineColor(const glm::vec3 &outlineColor);

	private:
		FontShader();

		/***********************************************************************
		* @description	: ��ȡ���� uniform ������λ��
		* @author		: Oscar Shen
		* @creat		: 2017��2��28��09:54:28
		***********************************************************************/
		virtual void getAllUniformLocation() override;

	};

} }



#endif // !SLOTH_FONT_SHADER_H_
