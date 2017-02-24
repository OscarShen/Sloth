/************************************************************************ 
* @project 		:  sloth
* @class   		:  NormalMappingShader
* @version 		:  v1.0.0
* @description	:  �ͷ�����ͼ��ɫ���� uniform �������Ӧ�������޸���ɫ������
* @author		:  Oscar Shen
* @creat 		:  2017��2��22��13:44:10
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

		int *m_LocLightPos;			// �ƹ�λ��
		int *m_LocLightColor;		// �ƹ���ɫ
		int *m_LocAttenuation;		// �ƹ�˥��

		int m_LocShininess;
		int m_LocReflectivity;
		int m_LocSkyColor;
		int m_LocNumberOfRows;
		int m_LocOffset;

		int m_LocClipPlane;			// �ü�ƽ�淽��

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
		* @description	: ��ʼ��ʱ��ȡ���б����� uniform location
		* @author		: Oscar Shen
		* @creat		: 2016��12��8��16:52:25
		***********************************************************************/
		virtual void getAllUniformLocation() override;

	};

} }


#endif // !SLOTH_NORMAL_MAPPING_SHADER_H_