#include "uniform_bool.h"

sloth::graphics::UniformBool::UniformBool(const std::string & name)
	: Uniform(name)
{
}

void sloth::graphics::UniformBool::loadBool(bool b)
{
	if (!m_Used || m_CurrentBool != b)
	{
		glProgramUniform1f(Uniform::getLocation(), Uniform::getLocation(), b ? 1.0f : 0.0f);
		m_Used = true;
		m_CurrentBool = b;
	}
}
