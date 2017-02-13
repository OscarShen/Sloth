#include "multiple_renderer.h"

namespace sloth { namespace graphics {

	MultipleRenderer::MultipleRenderer(Loader &loader)
	{
		enable_culling();
		m_ProjectionMatrix = glm::perspective(PERSPECTIVE_FOV, PERSPECTIVE_ASPECT,
			PERSPECTIVE_NEAR_PLANE, PERSPECTIVE_FAR_PLANE);
		m_StaticRenderer = new StaticRenderer(m_ProjectionMatrix);
		m_TerrainRenderer = new TerrainRenderer(m_ProjectionMatrix);
		m_SkyboxRenderer = new SkyboxRenderer(loader, m_ProjectionMatrix);
	}

	MultipleRenderer::~MultipleRenderer()
	{
		if(m_StaticRenderer!=nullptr)
			delete m_StaticRenderer;
		if (m_TerrainRenderer != nullptr)
			delete m_TerrainRenderer;
		if (m_SkyboxRenderer != nullptr)
			delete m_SkyboxRenderer;
	}

	void MultipleRenderer::render(const Light & sun, const RawCamera & camera, unsigned int cubeMapID)
	{
		// äÖÈ¾Ä£ÐÍ
		auto staticShader = StaticShader::inst();
		staticShader->loadLight(sun);
		staticShader->loadViewMatrix(camera);
		m_StaticRenderer->render(m_Entities);
		staticShader->loadSkyColor(FOG_COLOR_RED, FOG_COLOR_GREEN, FOG_COLOR_BLUE);
		// äÖÈ¾µØÐÎ
		auto terrainShader = TerrainShader::inst();
		terrainShader->loadLight(sun);
		terrainShader->loadViewMatrix(camera);
		m_TerrainRenderer->render(m_Terrains);
		terrainShader->loadSkyColor(FOG_COLOR_RED, FOG_COLOR_GREEN, FOG_COLOR_BLUE);
		// äÖÈ¾Ìì¿ÕºÐ
		auto skyboxShader = SkyboxShader::inst();
		m_SkyboxRenderer->render(cubeMapID, camera);

		// Clear up to avoid memory overflow, we will submit every entity per frame.
		m_Entities.clear();
		m_Terrains.clear();
	}

	void MultipleRenderer::render(const std::vector<Light>& lights, const RawCamera & camera, unsigned int cubeMapID)
	{
		// äÖÈ¾Ä£ÐÍ
		auto staticShader = StaticShader::inst();
		staticShader->loadLights(lights);
		staticShader->loadViewMatrix(camera);
		m_StaticRenderer->render(m_Entities);
		staticShader->loadSkyColor(FOG_COLOR_RED, FOG_COLOR_GREEN, FOG_COLOR_BLUE);
		// äÖÈ¾µØÐÎ
		auto terrainShader = TerrainShader::inst();
		terrainShader->loadLights(lights);
		terrainShader->loadViewMatrix(camera);
		m_TerrainRenderer->render(m_Terrains);
		terrainShader->loadSkyColor(FOG_COLOR_RED, FOG_COLOR_GREEN, FOG_COLOR_BLUE);
		// äÖÈ¾Ìì¿ÕºÐ
		auto skyboxShader = SkyboxShader::inst();
		m_SkyboxRenderer->render(cubeMapID, camera);
		skyboxShader->loadFogColor(FOG_COLOR_RED, FOG_COLOR_GREEN, FOG_COLOR_BLUE);

		// Clear up to avoid memory overflow, we will submit every entity per frame.
		m_Entities.clear();
		m_Terrains.clear();
	}

	void MultipleRenderer::submitTerrain(const Terrain & terrain)
	{
		m_Terrains.push_back(terrain);
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


} }
