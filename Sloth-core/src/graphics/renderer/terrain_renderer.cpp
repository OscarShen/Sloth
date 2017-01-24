#include "terrain_renderer.h"
#include "../../utils/error_check.h"
namespace sloth { namespace graphics {

	TerrainRenderer::TerrainRenderer(glm::mat4 & projection)
	{
		auto ts = TerrainShader::inst();
		ts->loadProjectionMatrix(projection);
		ts->connectTextureUnits();
	}

	void TerrainRenderer::render(std::vector<Terrain>& terrains)
	{
		TerrainShader::inst()->use();
glCheckError();
		for (auto it = terrains.begin(); it != terrains.end(); ++it) {
			prepareTerrain(*it);
glCheckError();
			loadModelMatrix(*it);
			glDrawElements(GL_TRIANGLES, it->getModel().getVertexCount(),
				GL_UNSIGNED_INT, nullptr);
			glBindVertexArray(0);
		}
	}

	void TerrainRenderer::prepareTerrain(Terrain & terrain)
	{
		RawModel rawModel = terrain.getModel();
		glBindVertexArray(rawModel.getVaoID());
glCheckError();
		bindMultiTerrain(terrain);
glCheckError();
	}

	void TerrainRenderer::loadModelMatrix(Terrain & terrain)
	{
		glm::mat4 model = util::Maths::createModelMatrix(glm::vec3(terrain.getX(), 0, terrain.getZ()), 0.0f, 0.0f, 0.0f, 1.0f);
		TerrainShader::inst()->loadModelMatrix(model);
	}

	void TerrainRenderer::bindMultiTerrain(Terrain & terrain)
	{
		auto tm = TextureManager2D::inst();
		auto multi_terrain = terrain.getMultiTerrain();
		glBindTextureUnit(0, tm->getTexture(multi_terrain.getBackgroundTexID())->getID());
		glBindTextureUnit(1, tm->getTexture(multi_terrain.getRedTexID())->getID());
		glBindTextureUnit(2, tm->getTexture(multi_terrain.getGreenTexID())->getID());
		glBindTextureUnit(3, tm->getTexture(multi_terrain.getBlueTexID())->getID());
		glBindTextureUnit(4, tm->getTexture(multi_terrain.getBlendMapTexID())->getID());
	}
} }
