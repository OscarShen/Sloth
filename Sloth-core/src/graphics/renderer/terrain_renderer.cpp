#include "terrain_renderer.h"
namespace sloth { namespace graphics {

	TerrainRenderer::TerrainRenderer(glm::mat4 & projection)
	{
		TerrainShader::inst()->loadProjectionMatrix(projection);
	}

	void TerrainRenderer::render(std::vector<Terrain>& terrains)
	{
		TerrainShader::inst()->use();
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
		TerrainShader::inst()->loadModelMatrix(model);
	}

} }

