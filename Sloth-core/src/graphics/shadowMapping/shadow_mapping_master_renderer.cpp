#include "shadow_mapping_master_renderer.h"
#include "shadow_mapping_shader.h"

namespace sloth { namespace graphics {

	const int ShadowMappingMasterRenderer::SHADOW_MAP_SIZE = 2048;

	void ShadowMappingMasterRenderer::render(const Light & light, const RawCamera & camera)
	{
		glm::vec3 lookAtPoint = camera.getPosition() + 80.0f * camera.getFront();
		glm::vec3 sunDir = glm::normalize(lookAtPoint - light.position);
		glm::mat4 view = glm::lookAt(lookAtPoint + (-sunDir * 100.0f), lookAtPoint, glm::vec3(0.0f, 1.0f, 0.0f));
		glm::mat4 projection = glm::ortho(-100.0f, 100.0f, -100.0f, 100.0f, 0.1f, 200.0f);

		auto shader = ShadowMappingShader::inst();
		shader->m_View.loadMatrix4(view);
		shader->m_Projection.loadMatrix4(projection);

		m_ShadowFbo.bindShadowFrameBuffer();
		m_Renderer.render(m_Entities);
		m_ShadowFbo.unbind();

		m_Entities.clear();
	}

	void ShadowMappingMasterRenderer::renderScene(const std::vector<std::shared_ptr<Entity>>& entities, const Light & light, const RawCamera & camera)
	{
		for (auto &i : entities)
			submitEntity(i);
		render(light, camera);
	}

	void ShadowMappingMasterRenderer::submitEntity(const Entity_s & entity)
	{
		TexturedModel &&model = entity->getTexturedModel();
		auto pos = m_Entities.find(model);
		if (pos != m_Entities.end()) {
			pos->second.push_back(entity);
		}
		else {
			m_Entities[model] = std::list<std::shared_ptr<Entity>>{ entity };
		}
	}

} }
