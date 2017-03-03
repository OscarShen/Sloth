#include "uniform_sampler.h"

sloth::graphics::UniformSampler::UniformSampler(const std::string & name)
	:Uniform(name)
{
}

void sloth::graphics::UniformSampler::loadTexUnit(int texUnit)
{
	if (!m_Used || m_CurrentValue != texUnit) {
		glProgramUniform1i(Uniform::getProgramID(), Uniform::getLocation(), texUnit);
		m_Used = true;
		m_CurrentValue = texUnit;
	}
}
