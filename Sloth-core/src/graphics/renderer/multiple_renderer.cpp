#include "multiple_renderer.h"

namespace sloth { namespace graphics {

	MultipleRenderer::MultipleRenderer()
	{
		auto &&projection = glm::perspective(PERSPECTIVE_FOV, PERSPECTIVE_ASPECT,
			PERSPECTIVE_NEAR_PLANE, PERSPECTIVE_FAR_PLANE);
		m_StaticRenderer = new StaticRenderer(projection);
		m_TerrainRenderer = new TerrainRenderer(projection);
	}

	MultipleRenderer::~MultipleRenderer()
	{
		delete m_StaticRenderer;
		delete m_TerrainRenderer;
	}

	void MultipleRenderer::render(const Light & sun, const Camera & camera)
	{
		auto staticShader = StaticShader::inst();
		staticShader->loadLight(sun);
		staticShader->loadViewMatrix(camera);
		m_StaticRenderer->render(m_Entities);
		auto terrainShader = TerrainShader::inst();
		terrainShader->loadLight(sun);
		terrainShader->loadViewMatrix(camera);
		m_TerrainRenderer->render(m_Terrains);
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
