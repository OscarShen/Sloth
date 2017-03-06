/************************************************************************ 
 * @project 	:  sloth
 * @class   	:  ParticleSystem
 * @version 	:  v1.0.0
 * @description :  ������������
 * @author		:  Oscar Shen
 * @creat 		:  2017��3��6��11:02:44
 * @revise 		:  
************************************************************************ 
 * Copyright @ OscarShen 2017. All rights reserved. 
************************************************************************/  
#pragma once
#ifndef SLOTH_PARTICLE_SYSTEM_H_
#define SLOTH_PARTICLE_SYSTEM_H_

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include "../../utils/timer.h"
#include "particle_master.h"
namespace sloth { namespace graphics {

	class ParticleSystem
	{
	private:
		float m_ParticlesPerSecond; // ÿ�������������
		float m_AverageSpeed; // ���ӵ�ƽ���ٶ� 
		float m_GravityComplient; // ���ӵ�����Ӱ���С 
		float m_AverageLifeLength; // ���ӵ�ƽ������
		float m_AverageScale; // ���ӵ�ƽ����С

		float m_SpeedError = 0.0f; // ���ӵ��ٶȶ������
		float m_LifeError = 0.0f; // ���ӵ������������
		float m_ScaleError = 0.0f; // ���ӵĴ�С�������

		bool m_RandomRotation = false; // �Ƿ������ת

		glm::vec3 m_Direction = glm::vec3(0.0f);
		float m_DirectionDeviation = 0.0f;

	public:
		/***********************************************************************
		* @description	: �����������ӵĻ����������������
						  particlesPerSecond : ÿ�����ɵ�������
						  speed : ���ӵĳ�ʼ�ٶ�
						  gravityComplent : ��������Ӱ��̶�
						  lifeLength : ���ӵ�����
						  scale : ���ӵĴ�С
		* @author		: Oscar Shen
		* @creat		: 2017��3��6��11:03:46
		***********************************************************************/
		constexpr ParticleSystem(float particlesPerSecond, float speed, float gravityComplent, float lifeLength, float scale)
			:m_ParticlesPerSecond(particlesPerSecond), m_AverageSpeed(speed), m_GravityComplient(gravityComplent), m_AverageLifeLength(lifeLength), m_AverageScale(scale) {}

		/***********************************************************************
		* @description	: ����ָ��λ�� systemCenter �����ӣ�������ӵ�ָ���� particleMaster ��
		* @author		: Oscar Shen
		* @creat		: 2017��3��6��11:03:46
		***********************************************************************/
		void generateParticles(const glm::vec3 &systemCenter, ParticleMaster &particleMaster);

		/***********************************************************************
		* @description	: �趨Բ׶������ϵͳ�ط����ƫ�ƶȣ����ǿ�ѡ��
		* @author		: Oscar Shen
		* @creat		: 2017��3��6��11:03:46
		***********************************************************************/
		inline void setDirection(const glm::vec3 &direction, float deviation) { m_Direction = direction; m_DirectionDeviation = deviation; }

		/***********************************************************************
		* @description	: ���������ת
		* @author		: Oscar Shen
		* @creat		: 2017��3��6��11:03:46
		***********************************************************************/
		inline void randomizeRotation() { m_RandomRotation = true; }

		/***********************************************************************
		* @description	: �趨�ٶ����ֵ
		* @author		: Oscar Shen
		* @creat		: 2017��3��6��11:03:46
		***********************************************************************/
		inline void setSpeedError(float error) { m_SpeedError = error * m_AverageSpeed; }

		/***********************************************************************
		* @description	: �趨�������ֵ
		* @author		: Oscar Shen
		* @creat		: 2017��3��6��11:03:46
		***********************************************************************/
		inline void setLifeError(float error) { m_LifeError = error * m_AverageLifeLength; }

		/***********************************************************************
		* @description	: �趨��С���ֵ
		* @author		: Oscar Shen
		* @creat		: 2017��3��6��11:03:46
		***********************************************************************/
		inline void setScaleError(float error) { m_ScaleError = error * m_AverageScale; }

	private:
		/***********************************************************************
		* @description	: ���䵥������
		* @author		: Oscar Shen
		* @creat		: 2017��3��6��11:03:46
		***********************************************************************/
		void emitParticle(const glm::vec3 &center, ParticleMaster &particleMaster);

		/***********************************************************************
		* @description	: �л�׼�������ֵ���������
		* @author		: Oscar Shen
		* @creat		: 2017��3��6��11:03:46
		***********************************************************************/
		float generateValue(float average, float errorMargin);

		/***********************************************************************
		* @description	: ������ת������ٶ�
		* @author		: Oscar Shen
		* @creat		: 2017��3��6��11:03:46
		***********************************************************************/
		float generateRotation();

		/***********************************************************************
		* @description	: ����Բ׶������
		* @author		: Oscar Shen
		* @creat		: 2017��3��6��11:03:46
		***********************************************************************/
		glm::vec3 generateRandomUnitVectorWithinCone(const glm::vec3 &coneDirection, float angle);

		/***********************************************************************
		* @description	: ����ֱ��������
		* @author		: Oscar Shen
		* @creat		: 2017��3��6��11:03:46
		***********************************************************************/
		glm::vec3 generateRandomUnitVector();
	};

} }


#endif // !SLOTH_PARTICLE_SYSTEM_H_
