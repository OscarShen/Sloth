#include "shadow_mapping_master_renderer.h"
#include "shadow_mapping_shader.h"

namespace sloth { namespace graphics {

	const int ShadowMappingMasterRenderer::SHADOW_MAP_SIZE = 2048;

	void ShadowMappingMasterRenderer::render(const MapedEntities &entities, const MapedEntities &normalMappingEntities, const std::list<std::shared_ptr<Terrain>> &terrains, const Light & light, const RawCamera & camera)
	{
		glm::vec3 lookAtPoint = camera.getPosition() + 80.0f * camera.getFront();
		glm::vec3 sunDir = glm::normalize(lookAtPoint - light.position);
		glm::mat4 view = glm::lookAt(lookAtPoint + (-sunDir * 100.0f), lookAtPoint, glm::vec3(0.0f, 1.0f, 0.0f));
		glm::mat4 projection = glm::ortho(-100.0f, 100.0f, -100.0f, 100.0f, 0.1f, 200.0f);
		m_LightSpace = projection * view;

		m_ShadowFbo.bindShadowFrameBuffer();

		auto shader = ShadowMappingShader::inst();
		shader->m_LightSpace.loadMatrix4(m_LightSpace);

		m_Renderer.render(entities, normalMappingEntities, terrains);

		m_ShadowFbo.unbind();
	}

} }
