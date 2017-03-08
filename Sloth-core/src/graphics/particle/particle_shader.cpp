#include "particle_shader.h"
namespace sloth { namespace graphics {

	std::shared_ptr<ParticleShader> ParticleShader::m_Inst(nullptr);

	std::shared_ptr<ParticleShader> ParticleShader::inst()
	{
		if (m_Inst.get() == nullptr)
			m_Inst = std::shared_ptr<ParticleShader>(new ParticleShader());
		return m_Inst;
	}

	ParticleShader::ParticleShader()
		:Shader(PARTICLE_VERTEX_SHADER,PARTICLE_FRAGMENT_SHADER)
	{
		std::vector<Uniform*> uniforms{ &projection, &numberOfRows };
		Shader::storeAllUniformLocation(uniforms);
	}

} }
