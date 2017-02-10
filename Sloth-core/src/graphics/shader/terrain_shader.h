/************************************************************************
* @project 		:  sloth
* @class   		:  TerrainShader
* @version 		:  v1.0.0
* @description	:  �͵�����ɫ��(terrain)�� uniform �������Ӧ�������޸���ɫ������
* @author		:  Oscar Shen
* @creat 		:  2016��10��8��14:52:32
* @revise 		:  2017��2��9��14:53:47
************************************************************************
* Copyright @ OscarShen 2017. All rights reserved.
*************************************************************************/
#pragma once
#ifndef SLOTH_TERRAIN_SHADER_H_
#define SLOTH_TERRAIN_SHADER_H_

#include "shader.h"
#include "../setup/macro.h"

namespace sloth { namespace graphics {

	class TerrainShader : public Shader
	{
	private:
		static TerrainShader *m_Inst;

		int m_LocModel;
		int m_LocView;
		int m_LocProjection;

		int *m_LocLightPos;			// �ƹ�λ��
		int *m_LocLightColor;		// �ƹ���ɫ
		int *m_LocAttenuation;		// �ƹ�˥��

		int m_LocShininess;
		int m_LocReflectivity;
		int m_LocSkyColor;
		int m_LocBackgroundTexture;
		int m_LocRTexture;
		int m_LocGTexture;
		int m_LocBTexture;
		int m_LocBlendMapTexture;


	public:
		static TerrainShader* inst();
		virtual ~TerrainShader();
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
		void loadSkyColor(const float r, const float g, const float b);
		void connectTextureUnits();

	private:
		TerrainShader();

	protected:
		/***********************************************************************
		* @description	: ��ʼ��ʱ��ȡ���б����� uniform location
		* @author		: Oscar Shen
		* @creat		: 2016��12��8��16:52:25
		***********************************************************************/
		virtual void getAllUniformLocation() override;
	};

} }


#endif // !SLOTH_TERRAIN_SHADER_H_
