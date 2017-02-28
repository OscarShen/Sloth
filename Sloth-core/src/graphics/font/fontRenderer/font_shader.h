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
		int m_LocColor;
		int m_LocModel;
		static FontShader *m_Inst;

	public:
		static FontShader* inst();

		void loadColor(const glm::vec3 &color);
		void loadModel(const glm::vec2 &model);

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
