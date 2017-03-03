#include "uniform_float.h"

sloth::graphics::UniformFloat::UniformFloat(const std::string & name)
	:Uniform(name)
{
}

void sloth::graphics::UniformFloat::loadFloat(float value)
{
	if (!m_Used || m_CurrentValue != value) {
		glProgramUniform1f(Uniform::getProgramID(), Uniform::getLocation(), value);
		m_Used = true;
		m_CurrentValue = value;
	}
}
