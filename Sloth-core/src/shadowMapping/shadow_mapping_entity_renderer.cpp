#include "shadow_mapping_entity_renderer.h"
#include "shadow_mapping_shader.h"
#include <terrain/terrain.h>
#include <entities/entity.h>
#include <utils/maths.h>

namespace sloth {

	void ShadowMapEntityRenderer::render(const MapedEntities & entities, const MapedEntities & normalMappingEntities, const std::list<std::shared_ptr<Terrain>> &terrains)
	{
		ShadowMappingShader::inst()->enable();

		for (auto it = entities.begin(); it != entities.end(); ++it) {
			glBindVertexArray(it->first.getRawModel().getVaoID());
			glBindTexture(GL_TEXTURE_2D, it->first.getTexture().getID());
			for (auto &entity : it->second) {
				prepareInstance(*entity);
				glDrawElements(GL_TRIANGLES, it->first.getRawModel().getVertexCount(), GL_UNSIGNED_INT, nullptr);
			}
		}

		for (auto it = normalMappingEntities.begin(); it != normalMappingEntities.end(); ++it) {
			glBindVertexArray(it->first.getRawModel().getVaoID());
			glBindTexture(GL_TEXTURE_2D, it->first.getTexture().getID());
			for (auto &entity : it->second) {
				prepareInstance(*entity);
				glDrawElements(GL_TRIANGLES, it->first.getRawModel().getVertexCount(), GL_UNSIGNED_INT, nullptr);
			}
		}

		for (auto it = terrains.begin(); it != terrains.end(); ++it) {
			glBindVertexArray((*it)->getModel().getVaoID());
			prepareTerrain(**it);
			glDrawElements(GL_TRIANGLES, (*it)->getModel().getVertexCount(), GL_UNSIGNED_INT, nullptr);
		}

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glBindVertexArray(0);
		ShadowMappingShader::inst()->disable();
	}

	void ShadowMapEntityRenderer::prepareInstance(const Entity & entity)
	{
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glm::mat4 model = Maths::createModelMatrix(
			entity.getPosition(), entity.getRotX(), entity.getRotY(), entity.getRotZ(), entity.getScale()
		);
		ShadowMappingShader::inst()->m_Model.loadMatrix4(model);
	}

	void ShadowMapEntityRenderer::prepareTerrain(const Terrain & terrain)
	{
		glEnableVertexAttribArray(0);
		glm::mat4 model = Maths::createModelMatrix(glm::vec3(terrain.getX(), 0, terrain.getZ()), 0.0f, 0.0f, 0.0f, 1.0f);
		ShadowMappingShader::inst()->m_Model.loadMatrix4(model);
	}

} 
