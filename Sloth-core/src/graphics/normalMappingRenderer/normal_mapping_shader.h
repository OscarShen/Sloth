/************************************************************************ 
* @project 		:  sloth
* @class   		:  NormalMappingShader
* @version 		:  v1.0.0
* @description	:  和法线贴图着色器的 uniform 变量相对应，用于修改着色器变量
* @author		:  Oscar Shen
* @creat 		:  2017年2月22日13:44:10
* @revise 		:  
************************************************************************ 
* Copyright @ OscarShen 2017. All rights reserved. 
************************************************************************/  
#pragma once
#ifndef SLOTH_NORMAL_MAPPING_SHADER_H_
#define SLOTH_NORMAL_MAPPING_SHADER_H_

#include "../shader/shader.h"
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include "../entities/light.hpp"
#include "../camera/camera.h"

#define NORMAL_MAPPING_VERTEX_FILE "src/shader/normalMap.vert"
#define NORMAL_MAPPING_FRAGMENT_FILE "src/shader/normalMap.frag"

namespace sloth { namespace graphics {

	class NormalMappingShader : public Shader
	{
	private:
		static NormalMappingShader *m_Inst;

		int m_LocModel;
		int m_LocView;
		int m_LocProjection;

		int *m_LocLightPos;			// 灯光位置
		int *m_LocLightColor;		// 灯光颜色
		int *m_LocAttenuation;		// 灯光衰减

		int m_LocShininess;
		int m_LocReflectivity;
		int m_LocSkyColor;
		int m_LocNumberOfRows;
		int m_LocOffset;

		int m_LocClipPlane;			// 裁剪平面方程

		int m_LocNormalMap;
		int m_LocDiffuseMap;

	public:
		static NormalMappingShader *inst();
		static void deleteShader() { delete m_Inst; }
		virtual ~NormalMappingShader();
		void loadModelMatrix(const glm::mat4 &model);
		void loadViewMatrix(const RawCamera &camera);
		void loadProjectionMatrix(const glm::mat4 &projection);
		void loadLight(const Light &light);
		void loadLights(const std::vector<Light> &lights);
		void loadShineVariable(const float shininess, const float reflectivity);
		void loadSkyColor(const float r, const float g, const float b);
		void loadNumberOfRows(int numberOfRaws);
		void loadOffset(float x, float y);
		void loadClipPlane(const glm::vec4 &clipPlane);

		void connectTextureUnit();
	private:
		NormalMappingShader();

	protected:
		/***********************************************************************
		* @description	: 初始化时获取所有变量的 uniform location
		* @author		: Oscar Shen
		* @creat		: 2016年12月8日16:52:25
		***********************************************************************/
		virtual void getAllUniformLocation() override;

	};

} }


#endif // !SLOTH_NORMAL_MAPPING_SHADER_H_