/************************************************************************ 
 * @project 	:  sloth
 * @class   	:  FontShader
 * @version 	:  v1.0.0
 * @description :  和字体着色器的 uniform 变量相对应，用于修改着色器变量
 * @author		:  Oscar Shen
 * @creat 		:  2017年2月28日09:55:18
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
		int m_LocColor; // 字体颜色
		int m_LocModel; // 字体的起始位置
		int m_LocFontWidth; // 字体的宽度
		int m_LocFontEdge; // 字体的渐变宽度
		int m_LocBorderWidth; // 字体的外轮廓宽度
		int m_LocBorderEdge; // 字体外轮廓的渐变宽度
		int m_LocOffset; // 字体的偏移值，可以产生字体的阴影
		int m_LocOutlineColor; // 字体外轮廓的颜色
		static FontShader *m_Inst;

	public:
		static FontShader* inst();

		static void cleanUp();

		/***********************************************************************
		* @description	: 加载字体颜色
		* @author		: Oscar Shen
		* @creat		: 2017年3月1日15:58:10
		***********************************************************************/
		void loadColor(const glm::vec3 &color);

		/***********************************************************************
		* @description	: 加载字体的起始位置
		* @author		: Oscar Shen
		* @creat		: 2017年3月1日15:58:23
		***********************************************************************/
		void loadModel(const glm::vec2 &model);

		/***********************************************************************
		* @description	: 加载字体的宽度
		* @author		: Oscar Shen
		* @creat		: 2017年3月1日15:58:23
		***********************************************************************/
		void loadFontWidth(float fontWidth);

		/***********************************************************************
		* @description	: 加载字体的渐变宽度
		* @author		: Oscar Shen
		* @creat		: 2017年3月1日15:58:23
		***********************************************************************/
		void loadFontEdge(float fontEdge);

		/***********************************************************************
		* @description	: 加载字体的外轮廓宽度
		* @author		: Oscar Shen
		* @creat		: 2017年3月1日15:58:23
		***********************************************************************/
		void loadBorderWidth(float borderWidth);

		/***********************************************************************
		* @description	: 加载字体外轮廓的渐变宽度
		* @author		: Oscar Shen
		* @creat		: 2017年3月1日15:58:23字体的偏移值，可以产生字体的阴影
		***********************************************************************/
		void loadBorderEdge(float borderEdge);

		/***********************************************************************
		* @description	: 加载字体的偏移值，可以产生字体的阴影
		* @author		: Oscar Shen
		* @creat		: 2017年3月1日15:58:23
		***********************************************************************/
		void loadOffset(const glm::vec2 &offset);

		/***********************************************************************
		* @description	: 加载字体外轮廓的颜色
		* @author		: Oscar Shen
		* @creat		: 2017年3月1日16:00:14
		***********************************************************************/
		void loadOutlineColor(const glm::vec3 &outlineColor);

	private:
		FontShader();

		/***********************************************************************
		* @description	: 获取所有 uniform 变量的位置
		* @author		: Oscar Shen
		* @creat		: 2017年2月28日09:54:28
		***********************************************************************/
		virtual void getAllUniformLocation() override;

	};

} }



#endif // !SLOTH_FONT_SHADER_H_
