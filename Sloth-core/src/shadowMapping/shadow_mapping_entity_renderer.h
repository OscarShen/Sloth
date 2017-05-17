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

#include <sloth.h>
#include <unordered_map>

namespace sloth { 
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

} 
#endif