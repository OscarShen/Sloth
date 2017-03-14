#include "terrain_renderer.h"
namespace sloth { namespace graphics {

	TerrainRenderer::TerrainRenderer(glm::mat4 & projection)
	{
		auto ts = TerrainShader::inst();
		ts->loadProjectionMatrix(projection);
		ts->connectTextureUnits();
	}

	void TerrainRenderer::render(std::list<Terrain_s>& terrains, unsigned int shadowMap)
	{
		TerrainShader::inst()->use();
		glBindTextureUnit(5, shadowMap);
		for (auto &i:terrains) {
			prepareTerrain(*i);
			loadModelMatrix(*i);
			glDrawElements(GL_TRIANGLES, i->getModel().getVertexCount(), GL_UNSIGNED_INT, nullptr);
			glBindVertexArray(0);
		}
	}

	void TerrainRenderer::prepareTerrain(Terrain & terrain)
	{
		// 地形暂时先设为 1,0
		TerrainShader::inst()->loadShineVariable(1.0f, 0.0f);
		RawModel rawModel = terrain.getModel();
		glBindVertexArray(rawModel.getVaoID());
		bindMultiTerrain(terrain);
	}

	void TerrainRenderer::loadModelMatrix(Terrain & terrain)
	{
		glm::mat4 model = util::Maths::createModelMatrix(glm::vec3(terrain.getX(), 0, terrain.getZ()), 0.0f, 0.0f, 0.0f, 1.0f);
		TerrainShader::inst()->loadModelMatrix(model);
	}

	void TerrainRenderer::bindMultiTerrain(Terrain & terrain)
	{
		auto terrainPack = terrain.getTexturePack();
		glBindTextureUnit(0, terrainPack.getBackgroundID());
		glBindTextureUnit(1, terrainPack.getRedID());
		glBindTextureUnit(2, terrainPack.getGreenID());
		glBindTextureUnit(3, terrainPack.getBlueID());
		glBindTextureUnit(4, terrainPack.getBlendMapID());
	}
} }
