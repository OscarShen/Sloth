/************************************************************************ 
 * @project 	:  sloth
 * @class   	:  WaterShader
 * @version 	:  v1.0.0
 * @description :  ��ˮ����ɫ��(water)�� uniform �������Ӧ�������޸���ɫ������
 * @author		:  Oscar Shen
 * @creat 		:  2017��2��13��18:41:57
 * @revise 		:  
************************************************************************ 
 * Copyright @ OscarShen 2017. All rights reserved. 
************************************************************************/  
#pragma once
#ifndef SLOTH_WATER_SHADER_H_
#define SLOTH_WATER_SHADER_H_

#include "shader.h"

namespace sloth { namespace graphics {

	class WaterShader : public Shader
	{
	private:
		static WaterShader *m_Inst;

		int m_LocModel;
		int m_LocView;
		int m_LocProjection;

	public:
		static WaterShader *inst();
		virtual ~WaterShader();

		/***********************************************************************
		* @description	: ����model����
		* @author		: Oscar Shen
		* @creat		: 2017��2��13��18:40:33
		***********************************************************************/
		void loadModelMatrix(const glm::mat4 &model);

		/***********************************************************************
		* @description	: ����view����
		* @author		: Oscar Shen
		* @creat		: 2017��2��13��18:40:33
		***********************************************************************/
		void loadViewMatrix(const RawCamera &camera);

		/***********************************************************************
		* @description	: ����projection����
		* @author		: Oscar Shen
		* @creat		: 2017��2��13��18:40:33
		***********************************************************************/
		void loadProjectionMatrix(const glm::mat4 &projection);

	private:
		WaterShader();


		/***********************************************************************
		* @description	: ��ʼ��ʱ��ȡ���б����� uniform location
		* @author		: Oscar Shen
		* @creat		: 2017��2��13��18:37:28
		***********************************************************************/
		virtual void getAllUniformLocation() override;
	};

} }



#endif // !SLOTH_WATER_SHADER_H_
