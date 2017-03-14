#include "shadow_mapping_entity_renderer.h"
#include "../../utils/maths.h"
#include "shadow_mapping_shader.h"

namespace sloth { namespace graphics {

	void ShadowMapEntityRenderer::render(const MapedEntities & entities)
	{
		ShadowMappingShader::inst()->enable();
		for (auto it = entities.begin(); it != entities.end(); ++it) {
			glBindVertexArray(it->first.getRawModel().getVaoID());
			glEnableVertexAttribArray(0);
			for (auto &entity : it->second) {
				prepareInstance(*entity);
				glDrawElements(GL_TRIANGLES, it->first.getRawModel().getVertexCount(), GL_UNSIGNED_INT, nullptr);
			}
		}
		glDisableVertexAttribArray(0);
		glBindVertexArray(0);
		ShadowMappingShader::inst()->disable();
	}

	void ShadowMapEntityRenderer::prepareInstance(const Entity & entity)
	{
		glm::mat4 model = util::Maths::createModelMatrix(
			entity.getPosition(), entity.getRotX(), entity.getRotY(), entity.getRotZ(), entity.getScale()
		);
		ShadowMappingShader::inst()->m_Model.loadMatrix4(model);
	}

} }
