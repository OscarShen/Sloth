/************************************************************************
* @project 		:  sloth
* @class   		:  Particle
* @version 		:  v1.0.0
* @description	:  �������ݴ洢��
* @author		:  Oscar Shen
* @creat 		:  2017��3��6��11:10:54
* @revise 		:  
************************************************************************
* Copyright @ OscarShen 2017. All rights reserved.
************************************************************************/
#pragma once
#ifndef SLOTH_PARTICLE_H_
#define SLOTH_PARTICLE_H_
#include <sloth.h>
#include <config/header.hpp>
#include "particle_texture.hpp"

namespace sloth {

	class Particle
	{
	private:
		glm::vec3 m_Position; // λ��
		glm::vec3 m_Velocity; // �ٶȣ�������ʾ�ٶȷ��򣬴�С��ʾ�ٶȿ���
		float m_GravityEffect; // ������С
		float m_LifeLength; // ������������
		float m_Rotation; // ������ת�̶ȣ���Ϊ���ӻ�һֱ�����Ļ����ֻ��һ����ת����
		float m_Scale; // �������Ŵ�С

		ParticleTexture m_Texture; // ��������

		glm::vec2 m_TexOffsetNow = glm::vec2(0.0f); // ��ǰ״̬�������ʼ��
		glm::vec2 m_TexOffsetNext = glm::vec2(0.0f); // ��һ״̬�������ʼ��
		float m_BlendFactor = 0.0f; // ������������Ļ��ϵ��

		float m_ElapsedTime = 0.0f; // �Ѵ��ڵ�ʱ��

		float m_Distance = 0.0f; // ���ӵ�����ľ��룬���ڽ�������

	public:
		/***********************************************************************
		* @description	: �������ݹ���
						  position : ����λ��
						  velocity : �ٶȵĴ�С�ͷ��򣬳��ȱ�ʾ��С
						  gravityEffect : ������Ӱ���С
						  lifeLength : ��������
						  rotation : ������ת�̶ȣ���Ϊ���ӻ�һֱ�����Ļ����ֻ��һ����ת����
						  scale : �������Ŵ�С
		* @author		: Oscar Shen
		* @creat		: 2017��3��6��11:03:46
		***********************************************************************/
		constexpr Particle(const ParticleTexture &particleTexture, const glm::vec3 &position, const glm::vec3 &velocity, float gravityEffect, float lifeLength, float rotation, float scale)
			:m_Texture(particleTexture), m_Position(position), m_Velocity(velocity), m_GravityEffect(gravityEffect), m_LifeLength(lifeLength),
			m_Rotation(rotation), m_Scale(scale) {}

		inline ParticleTexture getTexture() const { return m_Texture; }
		inline glm::vec3 getPosition() const { return m_Position; }
		inline float getRotation() const { return m_Rotation; }
		inline float getScale() const { return m_Scale; }

		/***********************************************************************
		* @description	: �������ӵ�ǰ״̬�������ʼ��
		* @author		: Oscar Shen
		* @creat		: 2017��3��6��17:04:01
		***********************************************************************/
		inline glm::vec2 getTexOffsetNow() const { return m_TexOffsetNow; }

		/***********************************************************************
		* @description	: ����������һ״̬�������ʼ��
		* @author		: Oscar Shen
		* @creat		: 2017��3��6��17:04:01
		***********************************************************************/
		inline glm::vec2 getTexOffsetNext() const { return m_TexOffsetNext; }

		inline float getBlendFactor() const { return m_BlendFactor; }
		inline float getDistance() const { return m_Distance; }


		/***********************************************************************
		* @description	: ÿ֡����һ�Σ���������״̬
		* @author		: Oscar Shen
		* @creat		: 2017��3��6��11:03:46
		***********************************************************************/
		bool update(const RawCamera &camera);

	private:
		/***********************************************************************
		* @description	: ���������е����������ƽ���ֳ� numberOfRow ���׶Σ������Ѿ�
						  ���Ӵ��ڵ������ж���Ҫ��ֵ����������
		* @author		: Oscar Shen
		* @creat		: 2017��3��6��11:03:46
		***********************************************************************/
		void updateTextureCoordInfo();

		/***********************************************************************
		* @description	: 
		* @author		: Oscar Shen
		* @creat		: 2017��3��6��11:03:46
		***********************************************************************/
		void setTextureOffset(glm::vec2 &offset, unsigned int index);
	};

} 


#endif // !SLOTH_PARTICLE_H_
