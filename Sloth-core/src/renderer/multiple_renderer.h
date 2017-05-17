/************************************************************************
 * @project 	:  sloth
 * @class   	:  MultipleRenderer
 * @version 	:  v1.0.1
 * @description	:  MultipleRenderer ��װ�� StaticRenderer �� TerrainRenderer
 				   ����ͨ����ͬ�Ĳ�����ģ�ͻ��ߵ��ν�����Ⱦ
 * @author		:  Oscar Shen
 * @creat 		:  2016��10��3��14:09:57
 * @revise 		:  2017��2��9��14:07:00
 ************************************************************************
 * Copyright @ OscarShen 2017. All rights reserved.
 ************************************************************************/
#pragma once
#ifndef SLOTH_MULTIPLE_RENDERER_H_
#define SLOTH_MULTIPLE_RENDERER_H_

#include <sloth.h>
#include "../renderer/static_renderer.h"
#include "../renderer/terrain_renderer.h"
#include "../renderer/skybox_renderer.h"
#include "../normalMappingRenderer/normal_mapping_renderer.h"
#include "../model/textured_model.hpp"
#include "../texture/cube_map_texture.hpp"
#include "../shadowMapping/shadow_mapping_master_renderer.h"

namespace sloth { 

	class MultipleRenderer
	{
	private:
		typedef std::unordered_map<TexturedModel, std::list<std::shared_ptr<Entity>>> MapedEntities;
		typedef std::shared_ptr<Entity> Entity_s;
		typedef std::shared_ptr<Terrain> Terrain_s;
		StaticRenderer *m_StaticRenderer;

		TerrainRenderer *m_TerrainRenderer;

		SkyboxRenderer *m_SkyboxRenderer;

		NormalMappingRenderer *m_NormapMappingRenderer;

		ShadowMappingMasterRenderer *m_ShadowMappingRenderer;

		MapedEntities m_NormalMappingEntities;
		MapedEntities m_Entities;

		std::list<Terrain_s> m_Terrains;

		// ���ڴ洢ͶӰ����
		glm::mat4 m_ProjectionMatrix;

	public:
		MultipleRenderer(Loader &loader);

		~MultipleRenderer();

		/************************************************************************
		* @description	: ��Ⱦ����ƹ��µ� ʵ�������Ρ���պ�
		* @author		: Oscar Shen
		* @creat		: 2017��2��9��14:03:27
		***********************************************************************/
		void render(const std::vector<Light> &lights, const RawCamera &camera, const CubeMapTexture &texture, const glm::vec4 &clipPlane);

		/***********************************************************************
		* @description	: ����model����
		* @author		: Oscar Shen
		* @creat		: 2017��2��13��18:40:33
		***********************************************************************/
		void renderScene(const std::vector<Entity_s> &entities,
			const std::vector<Entity_s> &normalMappingEntities,
			std::vector<Terrain_s> &terrains, 
			const std::vector<Light> &lights,
			const RawCamera &camera, const CubeMapTexture &texture, const glm::vec4 &clipPlane);

		void renderShadow(const std::vector<Entity_s>& entities, const std::vector<Entity_s> &normalMappingEntities, const std::vector<Terrain_s> &terrains, const Light &sun, const RawCamera &camera);

		void submitTerrain(const Terrain_s &terrain);
		void submitEntity(const Entity_s &entity);

		void submitNormalMappingEntity(const Entity_s &normalMappingEntity);

		/************************************************************************
		* @description	: ��ô洢�� projection ����
		* @author		: Oscar Shen
		* @creat		: 2017��2��12��19:12:21
		***********************************************************************/
		inline glm::mat4 getProjectionMatrix() const { return m_ProjectionMatrix; }
		inline unsigned int getShadowMap() const { return m_ShadowMappingRenderer->getShadowMap(); }
	};

} 

#endif // !SLOTH_MULTIPLE_RENDERER_H_
