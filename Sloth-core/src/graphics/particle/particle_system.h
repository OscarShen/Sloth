/************************************************************************ 
 * @project 	:  sloth
 * @class   	:  ParticleSystem
 * @version 	:  v1.0.0
 * @description :  用于生成粒子
 * @author		:  Oscar Shen
 * @creat 		:  2017年3月6日11:02:44
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
		float m_ParticlesPerSecond; // 每秒产生的粒子数
		float m_AverageSpeed; // 粒子的平均速度 
		float m_GravityComplient; // 粒子的重力影响大小 
		float m_AverageLifeLength; // 粒子的平均寿命
		float m_AverageScale; // 粒子的平均大小

		float m_SpeedError = 0.0f; // 粒子的速度抖动误差
		float m_LifeError = 0.0f; // 粒子的寿命抖动误差
		float m_ScaleError = 0.0f; // 粒子的大小抖动误差

		bool m_RandomRotation = false; // 是否随机旋转

		glm::vec3 m_Direction = glm::vec3(0.0f);
		float m_DirectionDeviation = 0.0f;

	public:
		/***********************************************************************
		* @description	: 设置生成粒子的基本参数——无误差
						  particlesPerSecond : 每秒生成的粒子数
						  speed : 粒子的初始速度
						  gravityComplent : 受重力的影响程度
						  lifeLength : 粒子的寿命
						  scale : 粒子的大小
		* @author		: Oscar Shen
		* @creat		: 2017年3月6日11:03:46
		***********************************************************************/
		constexpr ParticleSystem(float particlesPerSecond, float speed, float gravityComplent, float lifeLength, float scale)
			:m_ParticlesPerSecond(particlesPerSecond), m_AverageSpeed(speed), m_GravityComplient(gravityComplent), m_AverageLifeLength(lifeLength), m_AverageScale(scale) {}

		/***********************************************************************
		* @description	: 生成指定位置 systemCenter 的粒子，并且添加到指定的 particleMaster 中
		* @author		: Oscar Shen
		* @creat		: 2017年3月6日11:03:46
		***********************************************************************/
		void generateParticles(const glm::vec3 &systemCenter, ParticleMaster &particleMaster);

		/***********************************************************************
		* @description	: 设定圆锥形粒子系统地方向和偏移度，这是可选的
		* @author		: Oscar Shen
		* @creat		: 2017年3月6日11:03:46
		***********************************************************************/
		inline void setDirection(const glm::vec3 &direction, float deviation) { m_Direction = direction; m_DirectionDeviation = deviation; }

		/***********************************************************************
		* @description	: 开启随机旋转
		* @author		: Oscar Shen
		* @creat		: 2017年3月6日11:03:46
		***********************************************************************/
		inline void randomizeRotation() { m_RandomRotation = true; }

		/***********************************************************************
		* @description	: 设定速度误差值
		* @author		: Oscar Shen
		* @creat		: 2017年3月6日11:03:46
		***********************************************************************/
		inline void setSpeedError(float error) { m_SpeedError = error * m_AverageSpeed; }

		/***********************************************************************
		* @description	: 设定寿命误差值
		* @author		: Oscar Shen
		* @creat		: 2017年3月6日11:03:46
		***********************************************************************/
		inline void setLifeError(float error) { m_LifeError = error * m_AverageLifeLength; }

		/***********************************************************************
		* @description	: 设定大小误差值
		* @author		: Oscar Shen
		* @creat		: 2017年3月6日11:03:46
		***********************************************************************/
		inline void setScaleError(float error) { m_ScaleError = error * m_AverageScale; }

	private:
		/***********************************************************************
		* @description	: 发射单个粒子
		* @author		: Oscar Shen
		* @creat		: 2017年3月6日11:03:46
		***********************************************************************/
		void emitParticle(const glm::vec3 &center, ParticleMaster &particleMaster);

		/***********************************************************************
		* @description	: 有基准数和误差值生成随机数
		* @author		: Oscar Shen
		* @creat		: 2017年3月6日11:03:46
		***********************************************************************/
		float generateValue(float average, float errorMargin);

		/***********************************************************************
		* @description	: 产生旋转随机的速度
		* @author		: Oscar Shen
		* @creat		: 2017年3月6日11:03:46
		***********************************************************************/
		float generateRotation();

		/***********************************************************************
		* @description	: 生成圆锥形粒子
		* @author		: Oscar Shen
		* @creat		: 2017年3月6日11:03:46
		***********************************************************************/
		glm::vec3 generateRandomUnitVectorWithinCone(const glm::vec3 &coneDirection, float angle);

		/***********************************************************************
		* @description	: 生成直线型粒子
		* @author		: Oscar Shen
		* @creat		: 2017年3月6日11:03:46
		***********************************************************************/
		glm::vec3 generateRandomUnitVector();
	};

} }


#endif // !SLOTH_PARTICLE_SYSTEM_H_
