/************************************************************************ 
 * @project 	:  sloth
 * @class   	:  SkyboxShader
 * @version 	:  v1.0.0
 * @description :  和天空盒着色器(skybox)的 uniform 变量相对应，用于修改着色器变量
 * @author		:  Oscar Shen
 * @creat 		:  2017年2月10日13:56:39
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

		// 坐标变换矩阵
		int m_LocView;
		int m_LocProjection;

	public:
		/***********************************************************************
		* @description	: 单例模式获得 SkyboxShader 的实例
		* @author		: Oscar Shen
		* @creat		: 2017年2月10日13:51:27
		***********************************************************************/
		static SkyboxShader* inst();

		virtual ~SkyboxShader() {}

		/***********************************************************************
		* @description	: 加载 view 矩阵到 OpenGL
		* @author		: Oscar Shen
		* @creat		: 2017年2月10日13:54:48
		***********************************************************************/
		void loadViewMatrix(const RawCamera &camera);

		/***********************************************************************
		* @description	: 加载 projection 矩阵到 OpenGL
		* @author		: Oscar Shen
		* @creat		: 2017年2月10日13:55:04
		***********************************************************************/
		void loadProjectionMatrix(const glm::mat4 &projection);

	private:
		SkyboxShader();

		/***********************************************************************
		* @description	: 初始化时获取所有变量的 uniform location
		* @author		: Oscar Shen
		* @creat		: 2017年2月10日13:55:18
		***********************************************************************/
		virtual void getAllUniformLocation() override;
	};
} }



#endif // !SLOTH_SKYBOX_SHADER_H_
