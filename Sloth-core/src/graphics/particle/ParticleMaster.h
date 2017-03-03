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

		void update();

		void renderParticles(RawCamera &camera);

		void addParticle(const std::shared_ptr<Particle> &particle);
	};

} }



#endif // !SLOTH_PARTICLE_MASTER
