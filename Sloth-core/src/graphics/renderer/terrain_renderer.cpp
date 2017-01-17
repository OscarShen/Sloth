#include "terrain_renderer.h"
namespace sloth { namespace graphics {

	TerrainRenderer::TerrainRenderer()
	{
		m_Shader = TerrainShader::inst();
	}

	TerrainRenderer::TerrainRenderer(glm::mat4 & projection)
	{
		m_Shader = TerrainShader::inst();
		m_Shader->loadProjectionMatrix(projection);
	}

	void TerrainRenderer::render(std::vector<Terrain>& terrains)
	{
		for (auto it = terrains.begin(); it != terrains.end(); ++it) {
			prepareTerrain(*it);
			loadModelMatrix(*it);
			glDrawElements(GL_TRIANGLES, it->getModel().getVertexCount(),
				GL_UNSIGNED_INT, nullptr);
			glBindVertexArray(0);
		}
	}

	void TerrainRenderer::prepareTerrain(const Terrain & terrain)
	{
		RawModel rawModel = terrain.getModel();
		glBindVertexArray(rawModel.getVaoID());
		TextureManager2D *tm = TextureManager2D::inst();
		tm->activateTexUnit(0);
		tm->bindTexture(terrain.getTexID());
	}

	void TerrainRenderer::loadModelMatrix(Terrain & terrain)
	{
		glm::mat4 model = util::Maths::createModelMatrix(glm::vec3(terrain.getX(), 0, terrain.getZ()), 0.0f, 0.0f, 0.0f, 1.0f);
		m_Shader->loadModelMatrix(model);
	}

} }

