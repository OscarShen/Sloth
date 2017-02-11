/************************************************************************ 
 * @project 	:  sloth
 * @class   	:  SkyboxShader
 * @version 	:  v1.0.0
 * @description :  ����պ���ɫ��(skybox)�� uniform �������Ӧ�������޸���ɫ������
 * @author		:  Oscar Shen
 * @creat 		:  2017��2��10��13:56:39
 * @revise 		:  
************************************************************************ 
 * Copyright @ OscarShen 2017. All rights reserved. 
************************************************************************/  
#pragma once
#ifndef SLOTH_SKYBOX_SHADER_H_
#define SLOTH_SKYBOX_SHADER_H_

#include "shader.h"
#include "../setup/macro.h"

namespace sloth { namespace graphics {

	class SkyboxShader : public Shader
	{
	private:
		static SkyboxShader *m_Inst;

		// ����任����
		int m_LocView;
		int m_LocProjection;

		// ������ɫ
		int m_LocFogColor;

	public:
		/***********************************************************************
		* @description	: ����ģʽ��� SkyboxShader ��ʵ��
		* @author		: Oscar Shen
		* @creat		: 2017��2��10��13:51:27
		***********************************************************************/
		static SkyboxShader* inst();

		virtual ~SkyboxShader() {}

		/***********************************************************************
		* @description	: ���� view ���� OpenGL
		* @author		: Oscar Shen
		* @creat		: 2017��2��10��13:54:48
		***********************************************************************/
		void loadViewMatrix(const RawCamera &camera);

		/***********************************************************************
		* @description	: ���� projection ���� OpenGL
		* @author		: Oscar Shen
		* @creat		: 2017��2��10��13:55:04
		***********************************************************************/
		void loadProjectionMatrix(const glm::mat4 &projection);

		/***********************************************************************
		* @description	: ���� fogColor ���� OpenGL
		* @author		: Oscar Shen
		* @creat		: 2017��2��11��18:08:21
		***********************************************************************/
		void loadFogColor(float r, float g, float b);

	private:
		SkyboxShader();

		/***********************************************************************
		* @description	: ��ʼ��ʱ��ȡ���б����� uniform location
		* @author		: Oscar Shen
		* @creat		: 2017��2��10��13:55:18
		***********************************************************************/
		virtual void getAllUniformLocation() override;
	};
} }



#endif // !SLOTH_SKYBOX_SHADER_H_
