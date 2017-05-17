#include "shadow_mapping_shader.h"

namespace sloth {

	std::shared_ptr<ShadowMappingShader> ShadowMappingShader::inst()
	{
		static std::shared_ptr<ShadowMappingShader> m_Inst = nullptr;
		if (m_Inst.get() == nullptr)
			m_Inst = std::shared_ptr<ShadowMappingShader>(new ShadowMappingShader());
		return m_Inst;
	}
	ShadowMappingShader::ShadowMappingShader()
		: Shader(SHADOW_MAPPING_VERTEX_FILE, SHADOW_MAPPING_FRAGMENT_FILE)
	{
		storeAllUniformLocation(std::vector<Uniform*>{&m_Model, &m_LightSpace});
	}

} 