#include "particle_shader.h"
namespace sloth { namespace graphics {

	std::shared_ptr<ParticleShader> ParticleShader::m_Inst(nullptr);

	std::shared_ptr<ParticleShader> ParticleShader::inst()
	{
		if (m_Inst.get() == nullptr)
			m_Inst = std::shared_ptr<ParticleShader>(new ParticleShader());
		return m_Inst;
	}

	void ParticleShader::loadTextureCoordInfo(const glm::vec2 & offsetNow, const glm::vec2 & offsetNext, float numRows, float blend)
	{
		texOffsetNow.loadVec2(offsetNow);
		texOffsetNext.loadVec2(offsetNext);
		texCoordInfo.loadVec2(numRows, blend);
	}

	ParticleShader::ParticleShader()
		:Shader(PARTICLE_VERTEX_SHADER,PARTICLE_FRAGMENT_SHADER)
	{
		std::vector<Uniform*> uniforms{ &projection, &modelView, &texOffsetNow, &texOffsetNext, &texCoordInfo};
		Shader::storeAllUniformLocation(uniforms);
	}

} }
