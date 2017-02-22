#include "multiple_renderer.h"

namespace sloth { namespace graphics {

	MultipleRenderer::MultipleRenderer(Loader &loader)
	{
		m_ProjectionMatrix = glm::perspective(PERSPECTIVE_FOV, PERSPECTIVE_ASPECT,
			PERSPECTIVE_NEAR_PLANE, PERSPECTIVE_FAR_PLANE);
		m_StaticRenderer = new StaticRenderer(m_ProjectionMatrix);
		m_TerrainRenderer = new TerrainRenderer(m_ProjectionMatrix);
		m_SkyboxRenderer = new SkyboxRenderer(loader, m_ProjectionMatrix);
		m_NormapMappingRenderer = new NormalMappingRenderer(m_ProjectionMatrix);
	}

	MultipleRenderer::~MultipleRenderer()
	{
		if(m_StaticRenderer!=nullptr)
			delete m_StaticRenderer;
		if (m_TerrainRenderer != nullptr)
			delete m_TerrainRenderer;
		if (m_SkyboxRenderer != nullptr)
			delete m_SkyboxRenderer;
		if (m_NormapMappingRenderer != nullptr)
			delete m_NormapMappingRenderer;
	}

	void MultipleRenderer::render(const std::vector<Light>& lights, const RawCamera & camera, const CubeMapTexture &texture, const glm::vec4 & clipPlane)
	{
		// 渲染模型
		// 某些模型会被裁剪
		glDisable(GL_CULL_FACE);
		auto staticShader = StaticShader::inst();
		staticShader->loadClipPlane(clipPlane);
		staticShader->loadLights(lights);
		staticShader->loadViewMatrix(camera);
		staticShader->loadSkyColor(FOG_COLOR_RED, FOG_COLOR_GREEN, FOG_COLOR_BLUE);
		m_StaticRenderer->render(m_Entities);
		glEnable(GL_CULL_FACE);
		// 渲染有法线贴图的模型
		auto normalMappingShader = NormalMappingShader::inst();
		normalMappingShader->loadClipPlane(clipPlane);
		normalMappingShader->loadLights(lights);
		normalMappingShader->loadViewMatrix(camera);
		normalMappingShader->loadSkyColor(FOG_COLOR_RED, FOG_COLOR_GREEN, FOG_COLOR_BLUE);
		m_NormapMappingRenderer->render(m_NormalMappingEntities);
		// 渲染地形
		auto terrainShader = TerrainShader::inst();
		terrainShader->loadClipPlane(clipPlane);
		terrainShader->loadLights(lights);
		terrainShader->loadViewMatrix(camera);
		terrainShader->loadSkyColor(FOG_COLOR_RED, FOG_COLOR_GREEN, FOG_COLOR_BLUE);
		m_TerrainRenderer->render(m_Terrains);
		//// 渲染天空盒
		auto skyboxShader = SkyboxShader::inst();
		skyboxShader->loadFogColor(FOG_COLOR_RED, FOG_COLOR_GREEN, FOG_COLOR_BLUE);
		m_SkyboxRenderer->render(texture.getID(), camera);
		// Clear up to avoid memory overflow, we will submit every entity per frame.
		m_Entities.clear();
		m_Terrains.clear();
		m_NormalMappingEntities.clear();
	}

	void MultipleRenderer::renderScene(const std::vector<Entity>& entities, const std::vector<Entity> &normalMappingEntities, std::vector<Terrain*>& terrains, const std::vector<Light>& lights, const RawCamera & camera, const CubeMapTexture &texture, const glm::vec4 &clipPlane)
	{
		for (auto terrain : terrains) {
			submitTerrain(*terrain);
		}
		for (auto &i : entities) {
			submitEntity(i);
		}
		for (auto &i : normalMappingEntities) {
			submitNormalMappingEntity(i);
		}
		render(lights, camera, texture, clipPlane);
	}

	void MultipleRenderer::submitTerrain(Terrain & terrain)
	{
		m_Terrains.push_back(&terrain);
	}

	void MultipleRenderer::submitEntity(const Entity & entity)
	{
		TexturedModel &model = entity.getTexturedModel();
		auto pos = m_Entities.find(model);
		if (pos != m_Entities.end()) {
			pos->second.push_back(entity);
		}
		else {
			m_Entities.insert(std::pair<TexturedModel, std::vector<Entity>>(
				model, std::vector<Entity>{ entity }));
		}
	}

	void MultipleRenderer::submitNormalMappingEntity(const Entity & normalMappingEntity)
	{
		TexturedModel &model = normalMappingEntity.getTexturedModel();
		auto pos = m_NormalMappingEntities.find(model);
		if (pos != m_NormalMappingEntities.end()) {
			pos->second.push_back(normalMappingEntity);
		}
		else {
			m_NormalMappingEntities.insert(std::pair<TexturedModel, std::vector<Entity>>(
				model, std::vector<Entity>{ normalMappingEntity }));
		}
	}

} }
