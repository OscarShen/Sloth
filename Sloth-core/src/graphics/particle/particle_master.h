/************************************************************************ 
 * @project 	:  sloth
 * @class   	:  ParticleMaster
 * @version 	:  v1.0.0
 * @description :  �洢��ǰ���ɵ����ӣ����������������Ⱦ��
 * @author		:  Oscar Shen
 * @creat 		:  2017��3��6��11:15:14
 * @revise 		:  
************************************************************************ 
 * Copyright @ OscarShen 2017. All rights reserved. 
************************************************************************/  
#pragma once
#ifndef SLOTH_PARTICLE_MASTER
#define SLOTH_PARTICLE_MASTER
#include <list>
#include <unordered_map>
#include "particle.h"
#include "particle_renderer.h"
#include "insertion_sort.h"
namespace sloth { namespace graphics {

	class ParticleMaster
	{
	private:
		std::unordered_map<ParticleTexture, std::shared_ptr<std::list<std::shared_ptr<Particle>>>> m_Particles;
		
		ParticleRenderer m_Renderer;

	public:
		ParticleMaster(Loader &loader, const glm::mat4 &projection);

		/***********************************************************************
		* @description	: ÿ֡���ã����������д洢����������״̬
		* @author		: Oscar Shen
		* @creat		: 2017��3��6��11:03:46
		***********************************************************************/
		void update(const RawCamera &camera);

		/***********************************************************************
		* @description	: ��Ⱦ�����д洢����������
		* @author		: Oscar Shen
		* @creat		: 2017��3��6��11:03:46
		***********************************************************************/
		void renderParticles(RawCamera &camera);

		/***********************************************************************
		* @description	: ���������������
		* @author		: Oscar Shen
		* @creat		: 2017��3��6��11:03:46
		***********************************************************************/
		void addParticle(const std::shared_ptr<Particle> &particle);
	};

} }



#endif // !SLOTH_PARTICLE_MASTER
