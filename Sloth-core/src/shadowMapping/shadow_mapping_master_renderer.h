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
#ifndef SLOTH_SHADOW_MAPPING_MASTER_RENDERER_H_
#define SLOTH_SHADOW_MAPPING_MASTER_RENDERER_H_
#include <sloth.h>
#include "shadow_frame_buffer.h"
#include "shadow_mapping_entity_renderer.h"
namespace sloth {

	class ShadowMappingMasterRenderer
	{
		typedef std::unordered_map<TexturedModel, std::list<std::shared_ptr<Entity>>> MapedEntities;
		typedef std::shared_ptr<Entity> Entity_s;
	private:
		static const int SHADOW_MAP_SIZE;

		ShadowFrameBuffer m_ShadowFbo;
		ShadowMapEntityRenderer m_Renderer;

		glm::mat4 m_LightSpace;

	public:
		ShadowMappingMasterRenderer() : m_ShadowFbo(SHADOW_MAP_SIZE, SHADOW_MAP_SIZE) {}

		void render(const MapedEntities &entities, const MapedEntities &normalMappingEntities, const std::list<std::shared_ptr<Terrain>> &m_Terrains, const Light &light, const RawCamera &camera);

		inline unsigned int getShadowMap() const { return m_ShadowFbo.getDepthTexture(); }
		inline glm::mat4 getLightSpaceMatrix() const { return m_LightSpace; }
	};

} 

#endif // !SLOTH_SHADOW_MAPPING_MASTER_RENDERER_H_
