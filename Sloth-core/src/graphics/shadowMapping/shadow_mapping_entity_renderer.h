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
#ifndef SLOTH_SHADOW_MAP_ENTITY_RENDERER_H_
#define SLOTH_SHADOW_MAP_ENTITY_RENDERER_H_

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <unordered_map>
#include <list>
#include <memory>
#include "../entities/entity.h"
#include "../model/textured_model.hpp"
#include "../terrain/terrain.h"

namespace sloth { namespace graphics {

	class ShadowMapEntityRenderer
	{
		typedef std::unordered_map<TexturedModel, std::list<std::shared_ptr<Entity>>> MapedEntities;
		typedef std::shared_ptr<Entity> Entity_s;

	public:
		ShadowMapEntityRenderer() {}

		void render(const MapedEntities &entities, const MapedEntities & normalMappingEntities, const std::list<std::shared_ptr<Terrain>> &m_Terrains);

	private:
		void prepareInstance(const Entity &entity);

		void prepareTerrain(const Terrain &terrain);
	};

} }
#endif