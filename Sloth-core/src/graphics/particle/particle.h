/************************************************************************
* @project 	:  $rootnamespace$
* @class   	:  $safeitemrootname$
* @version 	:  v1.0.0
* @description :
* @author		:  $username$
* @creat 		:  $time$
* @revise 		:  $time$
************************************************************************
* Copyright @ OscarShen 2017. All rights reserved.
************************************************************************/
#pragma once
#ifndef SLOTH_PARTICLE_H_
#define SLOTH_PARTICLE_H_
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "../../config/header.hpp"
#include "../../utils/timer.h"
namespace sloth {
	namespace graphics {

		class Particle
		{
		private:
			glm::vec3 m_Position; // λ��
			glm::vec3 m_Velocity; // �ٶȣ�������ʾ�ٶȷ��򣬴�С��ʾ�ٶȿ���
			float m_GravityEffect; // ������С
			float m_LifeLength; // ������������
			float m_Rotation; // ������ת�̶ȣ���Ϊ���ӻ�һֱ�����Ļ����ֻ��һ����ת����
			float m_Scale; // �������Ŵ�С
			float m_ElapsedTime = 0.0f; // �Ѵ��ڵ�ʱ��

		public:
			constexpr Particle(const glm::vec3 &position, const glm::vec3 &velocity, float gravityEffect, float lifeLength, float rotation, float scale)
				:m_Position(position), m_Velocity(velocity), m_GravityEffect(gravityEffect), m_LifeLength(lifeLength),
				m_Rotation(rotation), m_Scale(scale) {}

			inline glm::vec3 getPosition() const { return m_Position; }
			inline float getRotation() const { return m_Rotation; }
			inline float getScale() const { return m_Scale; }

			bool update();
		};

	}
}


#endif // !SLOTH_PARTICLE_H_
