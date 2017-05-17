/************************************************************************
* @project 		:  sloth
* @class   		:  StaticShader
* @version 		:  v1.0.0
* @description	:  �ͻ�����ɫ��(basic)�� uniform �������Ӧ�������޸���ɫ������
* @author		:  Oscar Shen
* @creat 		:  2016��10��8��14:52:32
* @revise 		:  2017��2��9��14:53:47
************************************************************************
* Copyright @ OscarShen 2017. All rights reserved.
*************************************************************************/
#pragma once
#ifndef SLOTH_STATIC_SHADER_H_
#define SLOTH_STATIC_SHADER_H_

#include "shader.h"
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include <shader/uniform.h>
#include <entities/light.hpp>
#include <camera/camera.h>
#include "../config/header.hpp"

namespace sloth { 

	class StaticShader : public Shader
	{
	private:
		int m_LocDiffuseMap;

		int m_LocModel;
		int m_LocView;
		int m_LocProjection;

		int *m_LocLightPos;			// �ƹ�λ��
		int *m_LocLightColor;		// �ƹ���ɫ
		int *m_LocAttenuation;		// �ƹ�˥��

		int m_LocShininess;
		int m_LocReflectivity;
		int m_LocUseFakeLighting;
		int m_LocSkyColor;
		int m_LocNumberOfRows;
		int m_LocOffset;

		int m_LocClipPlane;			// �ü�ƽ�淽��

		int m_LocSpeculateMap;		// ������ͼ
		int m_LocUseSpecularMap;

	public:
		static std::shared_ptr<StaticShader> inst() {
			static std::shared_ptr<StaticShader> shader(new StaticShader());
			return shader;
		}
		virtual ~StaticShader();
		void loadModelMatrix(const glm::mat4 &model);
		void loadViewMatrix(const RawCamera &camera);
		void loadProjectionMatrix(const glm::mat4 &projection);
		void loadLight(const Light &light);

		/************************************************************************
		* @description	: ���صƹ���صı���ֵ����λ�á���ɫ��˥��
		* @author		: Oscar Shen
		* @creat		: 2017��2��8��16:52:25
		***********************************************************************/
		void loadLights(const std::vector<Light> &lights);

		void loadShineVariable(const float shininess, const float reflectivity);
		void loadUseFakeLighting(const bool useFake);
		void loadSkyColor(const float r, const float g, const float b);
		void loadNumberOfRows(int numberOfRaws);
		void loadOffset(float x, float y);
		void loadClipPlane(const glm::vec4 &clipPlane);
		void loadUseSpecularMap(bool useSpeMap);

	private:
		StaticShader();

		void connectTextureUnit();

	protected:
		/***********************************************************************
		* @description	: ��ʼ��ʱ��ȡ���б����� uniform location
		* @author		: Oscar Shen
		* @creat		: 2016��12��8��16:52:25
		***********************************************************************/
		virtual void getAllUniformLocation() override;
	};

} 


#endif // !SLOTH_STATIC_SHADER_H_
