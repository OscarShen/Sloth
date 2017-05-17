/************************************************************************
* @project 		:  sloth
* @class   		:  Particle
* @version 		:  v1.0.0
* @description	:  粒子数据存储类
* @author		:  Oscar Shen
* @creat 		:  2017年3月6日11:10:54
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
		glm::vec3 m_Position; // 位置
		glm::vec3 m_Velocity; // 速度，向量表示速度方向，大小表示速度快慢
		float m_GravityEffect; // 重力大小
		float m_LifeLength; // 粒子生命长度
		float m_Rotation; // 粒子旋转程度，因为粒子会一直面对屏幕，故只有一个旋转分量
		float m_Scale; // 粒子缩放大小

		ParticleTexture m_Texture; // 粒子纹理

		glm::vec2 m_TexOffsetNow = glm::vec2(0.0f); // 当前状态纹理的起始点
		glm::vec2 m_TexOffsetNext = glm::vec2(0.0f); // 下一状态纹理的起始点
		float m_BlendFactor = 0.0f; // 上述两种纹理的混合系数

		float m_ElapsedTime = 0.0f; // 已存在的时间

		float m_Distance = 0.0f; // 粒子到相机的距离，用于进行排序

	public:
		/***********************************************************************
		* @description	: 粒子数据构造
						  position : 粒子位置
						  velocity : 速度的大小和方向，长度表示大小
						  gravityEffect : 重力的影响大小
						  lifeLength : 寿命长杜
						  rotation : 粒子旋转程度，因为粒子会一直面对屏幕，故只有一个旋转分量
						  scale : 粒子缩放大小
		* @author		: Oscar Shen
		* @creat		: 2017年3月6日11:03:46
		***********************************************************************/
		constexpr Particle(const ParticleTexture &particleTexture, const glm::vec3 &position, const glm::vec3 &velocity, float gravityEffect, float lifeLength, float rotation, float scale)
			:m_Texture(particleTexture), m_Position(position), m_Velocity(velocity), m_GravityEffect(gravityEffect), m_LifeLength(lifeLength),
			m_Rotation(rotation), m_Scale(scale) {}

		inline ParticleTexture getTexture() const { return m_Texture; }
		inline glm::vec3 getPosition() const { return m_Position; }
		inline float getRotation() const { return m_Rotation; }
		inline float getScale() const { return m_Scale; }

		/***********************************************************************
		* @description	: 返回粒子当前状态纹理的起始点
		* @author		: Oscar Shen
		* @creat		: 2017年3月6日17:04:01
		***********************************************************************/
		inline glm::vec2 getTexOffsetNow() const { return m_TexOffsetNow; }

		/***********************************************************************
		* @description	: 返回粒子下一状态纹理的起始点
		* @author		: Oscar Shen
		* @creat		: 2017年3月6日17:04:01
		***********************************************************************/
		inline glm::vec2 getTexOffsetNext() const { return m_TexOffsetNext; }

		inline float getBlendFactor() const { return m_BlendFactor; }
		inline float getDistance() const { return m_Distance; }


		/***********************************************************************
		* @description	: 每帧调用一次，更新粒子状态
		* @author		: Oscar Shen
		* @creat		: 2017年3月6日11:03:46
		***********************************************************************/
		bool update(const RawCamera &camera);

	private:
		/***********************************************************************
		* @description	: 根据纹理集中的纹理个数，平均分成 numberOfRow 个阶段，根据已经
						  粒子存在的寿命判断需要插值的两种纹理。
		* @author		: Oscar Shen
		* @creat		: 2017年3月6日11:03:46
		***********************************************************************/
		void updateTextureCoordInfo();

		/***********************************************************************
		* @description	: 
		* @author		: Oscar Shen
		* @creat		: 2017年3月6日11:03:46
		***********************************************************************/
		void setTextureOffset(glm::vec2 &offset, unsigned int index);
	};

} 


#endif // !SLOTH_PARTICLE_H_
