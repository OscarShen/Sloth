/************************************************************************ 
 * @project 	:  sloth
 * @class   	:  ParticleMaster
 * @version 	:  v1.0.0
 * @description :  存储当前生成的粒子，并且视情况调用渲染器
 * @author		:  Oscar Shen
 * @creat 		:  2017年3月6日11:15:14
 * @revise 		:  
************************************************************************ 
 * Copyright @ OscarShen 2017. All rights reserved. 
************************************************************************/  
#pragma once
#ifndef SLOTH_PARTICLE_MASTER
#define SLOTH_PARTICLE_MASTER
#include <list>
#include "particle.h"
#include "particle_renderer.h"
namespace sloth { namespace graphics {

	class ParticleMaster
	{
	private:
		std::list<std::shared_ptr<Particle>> m_Particles;
		ParticleRenderer m_Renderer;

	public:
		ParticleMaster(Loader &loader, const glm::mat4 &projection);

		/***********************************************************************
		* @description	: 每帧调用，更新容器中存储的所有粒子状态
		* @author		: Oscar Shen
		* @creat		: 2017年3月6日11:03:46
		***********************************************************************/
		void update();

		/***********************************************************************
		* @description	: 渲染容器中存储的所有粒子
		* @author		: Oscar Shen
		* @creat		: 2017年3月6日11:03:46
		***********************************************************************/
		void renderParticles(RawCamera &camera);

		/***********************************************************************
		* @description	: 向容器中添加粒子
		* @author		: Oscar Shen
		* @creat		: 2017年3月6日11:03:46
		***********************************************************************/
		void addParticle(const std::shared_ptr<Particle> &particle);
	};

} }



#endif // !SLOTH_PARTICLE_MASTER
