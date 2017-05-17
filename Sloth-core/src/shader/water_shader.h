/************************************************************************ 
 * @project 	:  sloth
 * @class   	:  WaterShader
 * @version 	:  v1.0.0
 * @description :  和水面着色器(water)的 uniform 变量相对应，用于修改着色器变量
 * @author		:  Oscar Shen
 * @creat 		:  2017年2月13日18:41:57
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
		* @description	: 加载model矩阵
		* @author		: Oscar Shen
		* @creat		: 2017年2月13日18:40:33
		***********************************************************************/
		void loadModelMatrix(const glm::mat4 &model);

		/***********************************************************************
		* @description	: 加载view矩阵
		* @author		: Oscar Shen
		* @creat		: 2017年2月13日18:40:33
		***********************************************************************/
		void loadViewMatrix(const RawCamera &camera);

		/***********************************************************************
		* @description	: 加载projection矩阵
		* @author		: Oscar Shen
		* @creat		: 2017年2月13日18:40:33
		***********************************************************************/
		void loadProjectionMatrix(const glm::mat4 &projection);

		/***********************************************************************
		* @description	: 设定水波荡漾的程度
		* @author		: Oscar Shen
		* @creat		: 2017年2月20日14:31:16
		***********************************************************************/
		void loadMoveFactor(float factor);

		/***********************************************************************
		* @description	: 输入相机位置，计算 Fresnel Effect
		* @author		: Oscar Shen
		* @creat		: 2017年2月20日15:14:12
		***********************************************************************/
		void loadCameraPosition(const RawCamera &camera);

		/***********************************************************************
		* @description	: 载入灯光
		* @author		: Oscar Shen
		* @creat		: 2017年2月20日20:30:40
		***********************************************************************/
		void loadLight(const Light &light);

		/***********************************************************************
		* @description	: 绑定采样器单元——反射纹理、折射纹理、dudv map
		* @author		: Oscar Shen
		* @creat		: 2017年2月17日16:44:26
		***********************************************************************/
		void connectTextureUnit();

	private:
		WaterShader();


		/***********************************************************************
		* @description	: 初始化时获取所有变量的 uniform location
		* @author		: Oscar Shen
		* @creat		: 2017年2月13日18:37:28
		***********************************************************************/
		virtual void getAllUniformLocation() override;
	};

} 



#endif // !SLOTH_WATER_SHADER_H_
