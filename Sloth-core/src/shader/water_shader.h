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
#include "../entities/light.hpp"
#include <memory>

namespace sloth {
	class WaterShader : public Shader
	{
		typedef std::shared_ptr<WaterShader> WaterShader_s;
	private:
		static WaterShader_s m_Inst;

		int m_LocModel;
		int m_LocView;
		int m_LocProjection;
		int m_LocReflectionTexture;
		int m_LocRefractionTexture;
		int m_LocDudvMap;
		int m_LocMoveFactor;
		int m_LocCameraPosition;
		int m_LocNormalMap;
		int m_LocLightColor;
		int m_LocLightPosition;
		int m_LocDepthMap;

	public:
		static WaterShader_s inst();
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

		/***********************************************************************
		* @description	: �趨ˮ�������ĳ̶�
		* @author		: Oscar Shen
		* @creat		: 2017��2��20��14:31:16
		***********************************************************************/
		void loadMoveFactor(float factor);

		/***********************************************************************
		* @description	: �������λ�ã����� Fresnel Effect
		* @author		: Oscar Shen
		* @creat		: 2017��2��20��15:14:12
		***********************************************************************/
		void loadCameraPosition(const RawCamera &camera);

		/***********************************************************************
		* @description	: ����ƹ�
		* @author		: Oscar Shen
		* @creat		: 2017��2��20��20:30:40
		***********************************************************************/
		void loadLight(const Light &light);

		/***********************************************************************
		* @description	: �󶨲�������Ԫ��������������������dudv map
		* @author		: Oscar Shen
		* @creat		: 2017��2��17��16:44:26
		***********************************************************************/
		void connectTextureUnit();

	private:
		WaterShader();


		/***********************************************************************
		* @description	: ��ʼ��ʱ��ȡ���б����� uniform location
		* @author		: Oscar Shen
		* @creat		: 2017��2��13��18:37:28
		***********************************************************************/
		virtual void getAllUniformLocation() override;
	};

} 



#endif // !SLOTH_WATER_SHADER_H_
