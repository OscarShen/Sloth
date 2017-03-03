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
#ifndef SLOTH_PARTICLE_RENDERER_H_
#define SLOTH_PARTICLE_RENDERER_H_
#include <vector>
#include <list>
#include "../model/raw_model.hpp"
#include "../engine/loader.h"
#include "particle_shader.h"
#include "particle.h"
namespace sloth { namespace graphics {

	class ParticleRenderer
	{
	private:
		static std::vector<float> VERTICES;
		RawModel m_Quad;

	public:
		ParticleRenderer(Loader &loader, const glm::mat4 &projection);

		void render(std::list<std::shared_ptr<Particle>> &particles, RawCamera &camera);

	private:
		void prepare();

		void updateModelView(const glm::vec3 &position, float rotation, float scale, const glm::mat4 &view);

		void unbind();
	};

} }


#endif // !SLOTH_PARTICLE_RENDERER_H_
